/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2020/01/23 17:25:48 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		initialize_raytracer(t_raytracer *r)
{
	r->mlx_pointers[0] = mlx_init();
	r->mlx_pointers[1] = mlx_new_window(r->mlx_pointers[0], WIDTH, HEIGHT, "rtv1");
	r->mlx_pointers[2] = mlx_new_image(r->mlx_pointers[0], WIDTH, HEIGHT);
	r->image_data = (int *)mlx_get_data_addr(r->mlx_pointers[2],
		&r->mlx_properties[0], &r->mlx_properties[1], &r->mlx_properties[2]);
	r->plane_vectors[0] = vecnorm(r->scene.camera->vectors[2]);
	r->plane_vectors[1] = vecnorm(veccross(r->plane_vectors[0], r->scene.camera->vectors[1]));
}

void		ray_constructor(t_raytracer *r, int plane_indexes[2])
{
	double	scalars[2];

	scalars[X] = 2.0 * plane_indexes[X] / (double)WIDTH - 1;
	scalars[Y] = 2.0 * plane_indexes[Y] / (double)HEIGHT - 1;
	r->ray.org = r->scene.camera->vectors[0];
	r->ray.dir = vecnorm(vecadd(vecadd(vecadd(r->scene.camera->vectors[1], r->scene.camera->vectors[0]), vecopx(r->plane_vectors[X], scalars[X])), vecopx(r->plane_vectors[Y], scalars[Y])));
}

void		render_scene(t_raytracer *raytracer)
{
	int		plane_indexes[2];

	initialize_raytracer(raytracer);
	plane_indexes[X] = -1;
	while (++plane_indexes[X] < WIDTH)
	{
		plane_indexes[Y] = -1;
		while (++plane_indexes[Y] < HEIGHT)
		{
			ray_constructor(raytracer, plane_indexes);
			if (hit_loop(raytracer, BIG, NULL))
				raytracer->image_data[plane_indexes[Y] * WIDTH + plane_indexes[X]] = color_picker(raytracer);
		}
	}
	mlx_put_image_to_window(raytracer->mlx_pointers[0], raytracer->mlx_pointers[1], raytracer->mlx_pointers[2], 0, 0);
	mlx_loop(raytracer->mlx_pointers[0]);
}
