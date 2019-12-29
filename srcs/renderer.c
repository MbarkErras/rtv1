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

void	initialize_raytracer(t_raytracer *r)
{
    t_vec3    direction;

	r->mlx_pointers[0] = mlx_init();
	r->mlx_pointers[1] = mlx_new_window(r->mlx_pointers[0], WIDTH, HEIGHT, "rtv1");
	r->mlx_pointers[2] = mlx_new_image(r->mlx_pointers[0], WIDTH, HEIGHT);
	r->image_data = (int *)mlx_get_data_addr(r->mlx_pointers[2],
		&r->mlx_properties[0], &r->mlx_properties[1], &r->mlx_properties[2]);  
    direction = vecnorm(vecsub(r->scene.camera->vectors[0], r->scene.camera->vectors[1]));
    r->plane_vectors[0] = vecnorm(veccross(r->scene.camera->vectors[2], direction));
    r->plane_vectors[1] = vecnorm(veccross(r->plane_vectors[0], direction));
    r->left_corner = vecsub(vecsub(vecsub(r->scene.camera->vectors[0], direction), vecopx(r->plane_vectors[1], 0.58)), vecopx(r->plane_vectors[0], 0.58));
}

void	ray_constructor(t_raytracer *r, int plane_indexes[2])
{
	double      scalars[2];

	scalars[X] =  (2.0 * 0.58 *  plane_indexes[X]) / (double)WIDTH;
	scalars[Y] =  (2.0 * 0.58 * plane_indexes[Y]) / (double)HEIGHT;
	r->ray.org = r->scene.camera->vectors[0];
	r->ray.dir = vecnorm(vecsub(vecadd(vecadd(r->left_corner, r->scene.camera->vectors[1]), 
				vecadd(vecopx(r->plane_vectors[X], scalars[X]),
				vecopx(r->plane_vectors[Y], scalars[Y]))), r->scene.camera->vectors[0]));
}

void    render_scene(t_raytracer *raytracer)
{
    int         plane_indexes[2];

	initialize_raytracer(raytracer);
    plane_indexes[X] = -1;
    while (++plane_indexes[X] < WIDTH)
    {
        plane_indexes[Y] = -1;
        while (++plane_indexes[Y] < HEIGHT)
        {
            ray_constructor(raytracer, plane_indexes);         
            if (hit_loop(raytracer, BIG))
                raytracer->image_data[plane_indexes[Y] * WIDTH + plane_indexes[X]] =
                color_picker(raytracer);
        }
    }
    mlx_put_image_to_window(raytracer->mlx_pointers[0], raytracer->mlx_pointers[1],
		raytracer->mlx_pointers[2], 0,0);
    mlx_loop(raytracer->mlx_pointers[0]);
}