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

int    hit_procedure(t_hit hit)
{
    return (0);
}

int     hit_loop(double ray[3], t_hit *hit)
{
    return (0);
}

void    ray_constructor(double *ray, t_object camera, int plane_indexes[2], double plane_vectors[2][3])
{
    ray[0] = camera.vectors[0][0] + camera.vectors[1][0] + plane_vectors[0][0];
    ray[0] = camera.vectors[0][0] + camera.vectors[1][0] + plane_vectors[0][0];
    ray[0] = camera.vectors[0][0] + camera.vectors[1][0] + plane_vectors[0][0];
}

void    plane_vectors_constructor(t_scene *scene)
{



}

void    render_scene(t_scene scene)
{
    int         plane_indexes[2];
    double      ray[3];
    t_hit       hit;

    plane_vectors_constructor(&scene);
    plane_indexes[X] = -1;
    while (++plane_indexes[X] < WIDTH)
    {
        plane_indexes[Y] = -1;
        while (++plane_indexes[Y] < HEIGHT)
        {
            ray_constructor(ray, *scene.camera, plane_indexes, scene.plane_vectors);
            //printf("(%f, %f, %f)\n", ray[0], ray[1], ray[2]);
        }
    }
}