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
    (void)hit;
    return (0);
}

int     hit_loop(double ray[3], t_hit *hit)
{
    (void)ray;
    (void)hit;

    return (0);
}

void    ray_constructor(double *ray, t_object camera, int plane_indexes[2], double plane_z[2])
{
    ray[0] = camera.vectors[0][0] + camera.vectors[1][0];
    ray[1] = camera.vectors[0][1] + camera.vectors[1][1];
    ray[2] = camera.vectors[0][2] + camera.vectors[1][2] + (2 * plane_indexes[X] / WIDTH - 1) * plane_z[0] + (2 * plane_indexes[Y] / HEIGHT - 1) * plane_z[1];
}

void    render_scene(t_scene scene)
{
    int         plane_indexes[2];
    double      ray[3];
    double      plane_z[2];
    t_hit       hit;

    vplane_z = -1 * scene.camera->vectors[1][0] * tan(HFOV);
    hplane_z[1] = -1 * plane_z[0] * tan(VFOV);

    printf("plane_z: %f %f\n", plane_z[0], plane_z[1]);
    (void)hit;
    plane_indexes[X] = -1;
    while (++plane_indexes[X] < WIDTH)
    {
        plane_indexes[Y] = -1;
        while (++plane_indexes[Y] < HEIGHT)
        {
            ray_constructor(ray, *scene.camera, plane_indexes, plane_z);
            printf("(%f, %f, %f)\n", ray[0], ray[1], ray[2]);
            /*
            if (hit_loop(ray, &hit))
            {
                int color = hit_procedure(hit);
                //putpexil;
            }
            */
        }
    }
}