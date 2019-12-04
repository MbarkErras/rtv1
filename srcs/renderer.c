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

void    hit_procedure(int *hit)
{

}

int     *hit_loop(int *ray, t_list *objects)
{
    while (objects)
    {
        
        objects = objects->next;
    }
}

void    evaluate_plane(int *camera, int *direction, int *vplane, int *hplane)
{
    /*
    ** resizing length of {v} to {L}: resized_vector = L/||v||*v;
    */
    vplane[2] = -1 * direction[2] * tan(HFOV);
    hplane[2] = -1 * vplane[2] * tan(VFOV);
}

void    render_object()
{
    int camera[3] = {20, 0, 0};
    int direction[3] = {-1, 0, 0}; // direction vector can't be the null vector
    int vplane[3] = {0, 0, 0};
    int hplane[3] = {0, 0, 0};
    int ray[3];
    int rayline[3];
    int *hit;

    int y;
    int x = -1;
    evaluate_plane(camera, direction, vplane, hplane);
    while (++x < WIDTH)
    {
        y = -1;
        while (++y < HEIGHT)
        {
            ray[0] = camera[0] + direction[0] + (2 * x / WIDTH - 1) * hplane[0] + (2 * x / HEIGHT - 1) * vplane[0];
            ray[1] = camera[1] + direction[1] + (2 * x / WIDTH - 1) * hplane[1] + (2 * x / HEIGHT - 1) * vplane[1];
            ray[2] = camera[2] + direction[2] + (2 * x / WIDTH - 1) * hplane[2] + (2 * x / HEIGHT - 1) * vplane[2];
            if ((hit = hit_loop(ray))
                hit_procedure(hit);
        }
    }
}

void    render_scene(t_scene scene)
{
    
}