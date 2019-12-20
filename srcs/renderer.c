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
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, hit.color);
    return (0);
}

int     hit_loop(t_object camera, t_list *objects, double ray[3], t_hit *hit)
{
    double  shortest_hit_distance;
    double hit_distance;
    int color;

    shortest_hit_distance = INFINITY;
    while (objects)
    {
        if (TLIST(objects, t_object)->object_type == SPHERE)
            hit_sphere(camera, *TLIST(objects, t_object), ray, &hit_distance);
        if (hit_distance < shortest_hit_distance)
        {
            shortest_hit_distance = hit_distance;
            color = TLIST(objects, t_object)->scalars[0];
        }
        objects = objects->next;
    }
    return (shortest_hit_distance == INFINITY ? 0 : 1);
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
}

void    plane_vectors_constructor(t_scene scene, t_vec3 *planes_vectors)
{
    planes_vectors[0] = vecnorm(vecset(scene.camera->vectors[2][0],
        scene.camera->vectors[2][1], scene.camera->vectors[2][2]));
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

    plane_vectors_constructor(scene, plane_vectors);
    plane_indexes[X] = -1;
    while (++plane_indexes[X] < WIDTH)
    {
        plane_indexes[Y] = -1;
        while (++plane_indexes[Y] < HEIGHT)
        {
            ray_constructor(ray, *scene.camera, plane_indexes,
                                (t_vec3[2]){plane_vectors[0],
                                            plane_vectors[1]});
            if (hit_loop(*scene.camera, scene.objects, ray, &hit))
                hit_procedure(mlx_ptr, win_ptr, hit, plane_indexes[X], plane_indexes[Y]);
        }
    }
    mlx_loop(win_ptr);
}