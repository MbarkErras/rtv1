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

int     hit_plane(t_raytracer *r, double *distance)
{
    double      solution;

    solution = ((vecdot(r->hit.object->vectors[2], r->hit.object->vectors[0]) - 
        vecdot(r->hit.object->vectors[2], r->ray.org)) / 
        vecdot(r->hit.object->vectors[2], r->ray.dir));
    if (solution <= 0.0)
        return (0);
    *distance = solution;
    return (1);
}

int     hit_sphere(t_raytracer *r, double *distance)
{
    t_vec3      p_c;
    double      coef[4];
    double      solutions[2];

    p_c = vecsub(r->ray.org, r->hit.object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir);
    coef[1] = 2.0 * vecdot(p_c, r->ray.dir);
    coef[2] = vecdot(p_c, p_c) - pow(r->hit.object->scalars[1], 2);
    coef[3] = pow(coef[1], 2) - 4.0 * coef[0] * coef[2];
    if (coef[3] < 0.0)
        return (0);
    solutions[0] = (-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]);
    solutions[1] = (-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]);
    if (solutions[0] > 0.0 && solutions[1] > 0.0)
        *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
    else  if (solutions[0] < 0.0 && solutions[1] < 0.0)
        return (0);
    *distance = solutions[0] > solutions[1] ? solutions[0] : solutions[1];
    return (1);
}

int     hit_cylinder(t_raytracer *r, double *distance)
{
    t_vec3      p_c;
    double      coef[4];
    double      solutions[2];

    p_c = vecsub(r->ray.org, r->hit.object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir); 
    coef[1] = 2.0 * (vecdot(r->ray.dir, p_c) - 
        (vecdot(r->ray.dir, r->hit.object->vectors[3]) * 
        vecdot(p_c, r->hit.object->vectors[3])));
    coef[2] = vecdot(p_c, p_c) - pow(vecdot(p_c, r->hit.object->vectors[3]), 2) - 
        pow(r->hit.object->scalars[1], 2);
    coef[3] = pow(coef[1], 2) - 4.0 * coef[0] * coef[2];
    if (coef[3] < 0.0)
        return (0);
    solutions[0] = (-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]);
    solutions[1] = (-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]);
    if (solutions[0] > 0.0 && solutions[1] > 0.0)
        *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
    else  if (solutions[0] < 0.0 && solutions[1] < 0.0)
        return (0);
    *distance = solutions[0] > solutions[1] ? solutions[0] : solutions[1];
    return (1);
}

int     hit_cone(t_raytracer *r, double *distance)
{
    t_vec3      p_c;
    double      coef[4];
    double      solutions[2];

    p_c = vecsub(r->ray.org, r->hit.object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir) -
        (pow(vecdot(r->ray.dir, r->hit.object->vectors[3]), 2) / pow(cos(r->hit.object->scalars[1]), 2));
    coef[1] = 2.0 * (vecdot(r->ray.dir, p_c) -
        (vecdot(r->ray.dir, r->hit.object->vectors[3]) *
        vecdot(p_c, r->hit.object->vectors[3])) / pow(cos(r->hit.object->scalars[1]), 2));
    coef[2] = vecdot(p_c, p_c) - 
        (pow(vecdot(p_c, r->hit.object->vectors[3]), 2) / pow(cos(r->hit.object->scalars[1]), 2));
    coef[3] = pow(coef[1], 2) - 4.0 * coef[0] * coef[2];
    if (coef[3] < 0.0)
        return (0);
    solutions[0] = (-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]);
    solutions[1] = (-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]);
    if (solutions[0] > 0.0 && solutions[1] > 0.0)
        *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
    else  if (solutions[0] < 0.0 && solutions[1] < 0.0)
        return (0);
    *distance = solutions[0] > solutions[1] ? solutions[0] : solutions[1];
    return (1);
}