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

int     hit_plane(t_raytracer *r, t_object *object, double *distance)
{
    double      solution;
    t_vec3      direction;

    direction = vecnorm(object->vectors[1]);
    solution = ((vecdot(direction, object->vectors[0]) - 
        vecdot(direction, r->ray.org)) / 
        vecdot(direction, r->ray.dir));
    if (solution < 1e-4)
        return (0);
    *distance = solution;
    return (1);
}

int     hit_sphere(t_raytracer *r, t_object *object, double *distance)
{
    t_vec3      o_c;
    double      coef[4];
    double      solutions[2];

    o_c = vecsub(r->ray.org, object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir);
    coef[1] = 2.0 * vecdot(o_c, r->ray.dir);
    coef[2] = vecdot(o_c, o_c) - (object->scalars[1] * object->scalars[1]);
    coef[3] = (coef[1] * coef[1]) - (4.0 * coef[0] * coef[2]);
    if (coef[3] >= 0.0)
    {
        solutions[0] = (-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]);
        solutions[1] = (-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]);
        if ((solutions[0] > 1e-5 && solutions[1] < 1e-5) || (solutions[0] < 1e-5 && solutions[1] > 1e-5))
            return (0);
        else if (solutions[0] > 1e-5 && solutions[1] > solutions[0])
            *distance = solutions[0];
        else 
            *distance = solutions[1];
        if(*distance >= 1e-4)
            return (1);
    }
    return (0);
}

int     hit_cylinder(t_raytracer *r, t_object *object, double *distance)
{
    t_vec3      o_c;
    double      coef[4];
    double      solutions[2];

    o_c = vecsub(r->ray.org, object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir); 
    coef[1] = 2.0 * (vecdot(r->ray.dir, o_c) - 
        (vecdot(r->ray.dir, object->vectors[3]) * 
        vecdot(o_c, object->vectors[3])));
    coef[2] = vecdot(o_c, o_c) - pow(vecdot(o_c, object->vectors[3]), 2.0) - 
        pow(object->scalars[1], 2.0);
    coef[3] = pow(coef[1], 2.0) - 4.0 * coef[0] * coef[2];
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

int     hit_cone(t_raytracer *r, t_object *object, double *distance)
{
    t_vec3      o_c;
    double      coef[4];
    double      solutions[2];

    o_c = vecsub(r->ray.org, object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir) -
        (pow(vecdot(r->ray.dir, object->vectors[3]), 2.0) / pow(cos(object->scalars[1]), 2.0));
    coef[1] = 2.0 * (vecdot(r->ray.dir, o_c) -
        (vecdot(r->ray.dir, object->vectors[3]) *
        vecdot(o_c, object->vectors[3])) / pow(cos(object->scalars[1]), 2.0));
    coef[2] = vecdot(o_c, o_c) - 
        (pow(vecdot(o_c, object->vectors[3]), 2.0) / pow(cos(object->scalars[1]), 2.0));
    coef[3] = pow(coef[1], 2.0) - 4.0 * coef[0] * coef[2];
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