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
    color = 0;
    light = r->scene.lights;
    while (light)
    {
        pos_point = vecsub(r->hit.p, TLIST(light, t_object)->vectors[0]);
        reflect = vecreflect(r->ray.dir, r->hit.p);
        r->ray.org = r->hit.p;
        r->ray.dir = vecnorm(vecsub(TLIST(light, t_object)->vectors[0], r->hit.p));
       // if (!hit_loop(r, veclength(pos_point)))
       // {
        vecdot(vecnorm(pos_point), r->hit.normal) > 0.0 ? diffuse += vecdot(vecnorm(pos_point), r->hit.normal) : 0;
        vecdot(vecnorm(reflect), r->hit.normal) > 0.0 ?specular += pow(vecdot(vecnorm(reflect), r->hit.normal), 100.0) : 0;
        //}
        light = light->next;
    }
    rgb.x = (0.2 + diffuse + specular) * (((int)r->hit.object->scalars[0] >> 16) & 0xFF);
    rgb.y = (0.2 + diffuse + specular) * (((int)r->hit.object->scalars[0] >> 8) & 0xFF);
    rgb.z = (0.2 + diffuse + specular) * ((int)r->hit.object->scalars[0] & 0xFF);
    (rgb.x > 255.0) ? rgb.x = 255.0 : 0;
    (rgb.y > 255.0) ? rgb.y = 255.0 : 0;
    (rgb.z > 255.0) ? rgb.z = 255.0 : 0;
    color = (((int)rgb.x & 0x0ff) << 16) | (((int)rgb.y & 0x0ff) << 8) | ((int)rgb.z & 0x0ff);
    return (color);
}

// double		clamping(double color)
// {
// 	if (color < 0.0)
// 		color = 0.0;
// 	if (color > 255.0)
// 		color = 255.0;
// 	return (color);
// }

// int      hidding(t_raytracer *r, t_list *light)
// {
//     t_list   *objects;
//     double   big;

//     r->ray.org = r->hit.p;
//     r->ray.dir = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
//     big = veclength(r->ray.dir);
//     r->ray.dir = vecnorm(r->ray.dir);
//     objects = r->scene.objects;
//     while (objects)
//     {
//         if (TLIST(objects, t_object) != r->hit.object)
//             if (hit_loop(r, big))
//                 return (1);
//         objects = objects->next;
//     }
//     return (0);
// }

// double  specular(t_raytracer *r, t_vec3 vector)
// {
//     t_vec3  reflect;
//     double  specular;
//     double  dot;

//     specular = 0.0;
//     vector = vecnorm(vector);
//     reflect = vecreflect(vector, r->hit.p);
//     dot = vecdot(reflect, r->ray.dir);
//     dot > 0.0 ? specular = pow(dot, 44.0) : 0;
//     return (clamping(specular));
// }

// t_vec3  double_to_rgb(double value, double coef)
// {
//     t_vec3  rgb;

//     rgb.x = coef * (((int)value >> 16) & 0xFF);
//     rgb.y = coef * (((int)value >> 8) & 0xFF);
//     rgb.z = coef * ((int)value & 0xFF);
//     return (rgb);
// }

// int     rgb_to_int(t_vec3 rgb)
// {
//     int color;
    
//     color = (((int)rgb.x & 0x0ff) << 16) |
//         (((int)rgb.y & 0x0ff) << 8) |
//         ((int)rgb.z & 0x0ff);
//         return (color);
// }
// int     color_picker(t_raytracer *r)
// {
//     t_list  *light;
//     t_vec3  vector;
//     t_vec3  diffuse;
//     double  coef;
//     int     hide;

//     coef = 0.0;
//     diffuse = double_to_rgb(r->hit.object->scalars[0], 0.15);
//     light = r->scene.lights;
//     while (light)
//     {
//         hide = hidding(r, light);
//         vector = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
//         (hide == 0) ? coef += clamping(vecdot(vecnorm(vector), r->hit.normal)) : 0;
//         diffuse = vecadd(diffuse, double_to_rgb(r->hit.object->scalars[0], coef));
//         if(hide == 0)
//             diffuse = vecopplus(diffuse, specular(r, vector));
//         light = light->next;
//     }
//     return (rgb_to_int(diffuse));
// }

// int red = (rgb >> 16) & 0xFF;
// int green = (rgb >> 8) & 0xFF;
// int blue = rgb & 0xFF;


// 1111 1010   1010 1001    1100 1100


// 1111 1111   1111 1010    1010 1001
// 0000 0000   0000 0000    1111 1111