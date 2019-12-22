/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 06:00:24 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int    hit_procedure(void *mlx_ptr, void *win_ptr, t_hit hit, int x, int y)
{
        if (x == 750 && y == 500)
        {
            printf("########### coloring\n");
        }
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xffffff);
    return (0);
}

int     hit_loop(t_object camera, t_list *objects, double ray[3], t_hit *hit, int x, int y)
{
    double  shortest_hit_distance;
    double hit_distance;
    int color;

    shortest_hit_distance = BIG;
    hit_distance = BIG;
    while (objects)
    {
        if (TLIST(objects, t_object)->object_type == SPHERE)
            hit_sphere(camera, *TLIST(objects, t_object), ray, &hit_distance, x, y);
        if (x == 750 && y == 500)
        {
            printf("########### %f %f\n", hit_distance, shortest_hit_distance);
        }
        if (hit_distance < shortest_hit_distance)
        {
            shortest_hit_distance = hit_distance;
            color = TLIST(objects, t_object)->scalars[0];
          if (x == 750 && y == 500)
        {
            printf("final########### %f \n", shortest_hit_distance);
        }
        }
        objects = objects->next;
    }
    return (shortest_hit_distance == BIG ? 0 : 1);
}

void    ray_constructor(double *ray, t_object camera,
                        int plane_indexes[2], t_vec3 planes[2])
{
    double scalarh = 2 * plane_indexes[0] / (double)WIDTH - 1;
    double scalarv = 2 * plane_indexes[1] / (double)HEIGHT - 1;
    ray[0] = camera.vectors[0][0] + camera.vectors[1][0] +
            scalarh * planes[0].x + scalarv * planes[1].x;
    ray[1] = camera.vectors[0][1] + camera.vectors[1][1] +
            scalarh * planes[0].y + scalarv * planes[1].y;
    ray[2] = camera.vectors[0][2] + camera.vectors[1][2] +
            scalarh * planes[0].z + scalarv * planes[1].z;
    // if ((plane_indexes[X] == 0 && plane_indexes[Y] == 0) ||
    //         (plane_indexes[X] == WIDTH - 1 && plane_indexes[Y] == 0) ||
    //         (plane_indexes[X] == 0 && plane_indexes[Y] == HEIGHT - 1) ||
    //         (plane_indexes[X] == WIDTH - 1 && plane_indexes[Y] == HEIGHT - 1))
    //     printf("(%f, %f, %f)\n", ray[0], ray[1], ray[2]);
}

void    plane_vectors_constructor(t_scene scene, t_vec3 *planes_vectors)
{
    planes_vectors[0] = vecnorm((t_vec3){scene.camera->vectors[2][0],
        scene.camera->vectors[2][1], scene.camera->vectors[2][2]});
    planes_vectors[1] = vecnorm(veccross((t_vec3){scene.camera->vectors[1][0],
        scene.camera->vectors[1][1], scene.camera->vectors[1][2]},
        planes_vectors[0]));
}

void    render_scene(t_scene scene)
{
    int         plane_indexes[2];
    t_vec3      plane_vectors[2];
    double      ray[3];
    t_hit       hit;
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "rtv1");
    void *img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
    int bpp;
    int sl;
    int e;
    int *img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &e);

    plane_vectors_constructor(scene, plane_vectors);
    printf("plane vectors:\n (%f, %f, %f)\t(%f, %f , %f)\n", plane_vectors[0].x, plane_vectors[0].y, plane_vectors[0].z, plane_vectors[1].x, plane_vectors[1].y, plane_vectors[1].z);
    plane_indexes[X] = -1;
    while (++plane_indexes[X] < WIDTH)
    {
        plane_indexes[Y] = -1;
        while (++plane_indexes[Y] < HEIGHT)
        {
            ray_constructor(ray, *scene.camera, plane_indexes,
                                (t_vec3[2]){plane_vectors[0],
                                            plane_vectors[1]});
            //printf("(%f, %f, %f)", ray[0], ray[1], ray[2]);
            
            if (hit_loop(*scene.camera, scene.objects, ray, &hit, plane_indexes[X], plane_indexes[Y]))
            {
                if (plane_indexes[X] == 750 && plane_indexes[Y] == 500)
                    printf("XCXCCXCX\n");
                img_data[plane_indexes[Y] * WIDTH + plane_indexes[X]] = 0xffffff;
                //mlx_pixel_put(mlx_ptr, win_ptr, plane_indexes[X], plane_indexes[Y], 0xffffff);
               // hit_procedure(mlx_ptr, win_ptr, hit, plane_indexes[X], plane_indexes[Y]);
                //printf("hit!\n");
            }
            else
            {
                //printf("not hit!\n");
            }
            if (plane_indexes[X] == 750 && plane_indexes[Y] == 500)
            {
                printf("(%f, %f, %f)\n", ray[0], ray[1], ray[2]);
            }
        }
    }
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0,0);
    mlx_loop(mlx_ptr);
}