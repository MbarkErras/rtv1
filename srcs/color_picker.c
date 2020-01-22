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

#include "../includes/rtv1.h"

// static int      hidding(t_raytracer r, t_list *light)
// {
//     double   big;
//     t_raytracer tmp;

//     r.ray.org = r.hit.p;
//     r.ray.dir = vecsub(r.hit.p, TLIST(light, t_object)->vectors[0]);
//     big = veclength(r.ray.dir);
//     r.ray.dir = vecnorm(r.ray.dir);
//     if (hit_loop(&r, big, 1, r.hit.object))
//     {
//         r.ray.org = tmp.ray.org;
//         r.ray.dir = tmp.ray.dir;
//         return (1);
//     }
//     r.ray.org = tmp.ray.org;
//     r.ray.dir = tmp.ray.dir;
//     return (0);
// }

static int     rgb_to_int(t_vec3 rgb)
{
    int color;
    
    color = (((int)rgb.x & 0x0ff) << 16) |
        (((int)rgb.y & 0x0ff) << 8) |
        ((int)rgb.z & 0x0ff);
        return (color);
}

t_vec3  d_to_rgb(double value, double coef)
{
    t_vec3  rgb;

    rgb.x = coef * (((int)value >> 16) & 0xFF);
    rgb.y = coef * (((int)value >> 8) & 0xFF);
    rgb.z = coef * ((int)value & 0xFF);
    return (rgb);
}

static t_vec3   diffuse(t_raytracer *r, t_list *light)
{
    t_vec3  vector;
    double  color;

    color = 0.0;
    vector = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
    if (vecdot(vecnorm(vector), r->hit.normal) > 0.0)
        color = vecdot(vecnorm(vector), r->hit.normal);  
    return (vecopx(d_to_rgb(r->hit.object->scalars[0], color),
        TLIST(light, t_object)->scalars[1] * 256 / veclength(vector)));  
}

static t_vec3   specular(t_raytracer *r, t_list *light)
{
    t_vec3  vector;
    t_vec3  reflect;
    double  color;

    color = 0.0;
    vector = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
    reflect = vecnorm(vecreflect(vector, r->hit.normal));
    if (vecdot(reflect, r->ray.dir) > 0.0) 
        color += pow(vecdot(reflect, r->hit.normal), 50.0);
    return (vecopx(vecset(color, color, color), 255.99));
}

int     color_picker(t_raytracer *r)
{
    t_vec3  rgb;
    t_list  *light;
    //  int     hide;

    rgb = vecset(0.0, 0.0, 0.0);
    light = r->scene.lights;
    while (light)
    {
        // hide = hidding(*r, light);
        //   if(hide != 0)
            rgb = vecadd(rgb, diffuse(r, light));
            rgb = vecadd(rgb, specular(r, light));
        light = light->next;
    }
    rgb.x += 0.2  * (((int)r->hit.object->scalars[0] >> 16) & 0xFF);
    rgb.y += 0.2 * (((int)r->hit.object->scalars[0] >> 8) & 0xFF);
    rgb.z += 0.2 * ((int)r->hit.object->scalars[0] & 0xFF);
    clamping_vector(&rgb);
    return (rgb_to_int(rgb));
}


// int red = (rgb >> 16) & 0xFF;
// int green = (rgb >> 8) & 0xFF;
// int blue = rgb & 0xFF;


// 1111 1010   1010 1001    1100 1100


// 1111 1111   1111 1010    1010 1001
// 0000 0000   0000 0000    1111 1111
