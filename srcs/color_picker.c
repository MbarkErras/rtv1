/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 23:19:30 by aait-el-          #+#    #+#             */
/*   Updated: 2019/12/24 23:19:32 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int     color_picker(t_raytracer *r)
{
    int     color;
    double  diffuse;
    double  specular;
    t_vec3  rgb;
    t_vec3  pos_point;
    t_vec3  reflect;
    t_list  *light;

    diffuse = 0.0;
    specular = 0.0;
    light = r->scene.lights;
    while (light)
    {
        pos_point = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
        reflect = vecreflect(r->ray.dir, r->hit.p);

        r->ray.org = r->hit.p;
        r->ray.dir = vecnorm(vecsub(r->hit.p, TLIST(light, t_object)->vectors[0]));
        if (!hit_loop(r, veclength(pos_point)))
        {
            diffuse += vecdot(vecnorm(pos_point), r->hit.normal);
            specular += pow(vecdot(vecnorm(reflect), r->hit.normal), 40.0);
        }
        light = light->next;
    }
    rgb.x = (0.25 + diffuse + specular) * (((int)r->hit.object->scalars[0] >> 16) & 0xFF);
    rgb.y = (0.25 + diffuse + specular) * (((int)r->hit.object->scalars[0] >> 8) & 0xFF);
    rgb.z = (0.25 + diffuse + specular) * ((int)r->hit.object->scalars[0] & 0xFF);
    color = (((int)rgb.x & 0x0ff) << 16) | (((int)rgb.y & 0x0ff) << 8) | ((int)rgb.z & 0x0ff);
    return (color);
}






// int red = (rgb >> 16) & 0xFF;
// int green = (rgb >> 8) & 0xFF;
// int blue = rgb & 0xFF;


// 1111 1010   1010 1001    1100 1100

// 1111 1111   1111 1010    1010 1001
// 0000 0000   0000 0000    1111 1111