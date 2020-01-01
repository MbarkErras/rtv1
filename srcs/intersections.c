 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <mbarekerras@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2019/12/29 17:44:41 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"



int     hit_plane(t_raytracer *r, t_object *object, double *distance)
{
    double      solution;
	t_vec3		c_o;

	c_o = vecsub(object->vectors[0], r->ray.org);
    solution = vecdot(object->vectors[1], c_o) / vecdot(object->vectors[1], r->ray.dir);
    if (solution <= 0.0)
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
    coef[2] = vecdot(o_c, o_c) - pow(object->scalars[1], 2);
    coef[3] = pow(coef[1], 2) - 4.0 * coef[0] * coef[2];
    if (coef[3] < 0.0)
        return (0);
    solutions[0] = (-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]);
    solutions[1] = (-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]);
    if (solutions[0] > 0.0 && solutions[1] > 0.0)
        *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
    else  if (solutions[0] < 0.0 && solutions[1] < 0.0)
        return (0);
	else
    	*distance = solutions[0] > solutions[1] ? solutions[0] : solutions[1];
    return (1);
}

int     hit_cylinder(t_raytracer *r, t_object *object, double *distance)
{
    t_vec3      o_c;
    double      coef[4];
    double      solutions[2];

    o_c = vecsub(r->ray.org, object->vectors[0]);
    coef[0] = vecdot(r->ray.dir, r->ray.dir) -  pow(vecdot(r->ray.dir, object->vectors[3]), 2); 
    coef[1] = 2.0 * (vecdot(r->ray.dir, o_c) - 
        (vecdot(r->ray.dir, object->vectors[3]) * 
        vecdot(o_c, object->vectors[3])));
    coef[2] = vecdot(o_c, o_c) - pow(vecdot(o_c, object->vectors[3]), 2) - 
        pow(object->scalars[1], 2);
    coef[3] = pow(coef[1], 2) - 4.0 * coef[0] * coef[2];
    if (coef[3] < 0.0)
        return (0);
    solutions[0] = (-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]);
    solutions[1] = (-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]);
    if (solutions[0] > 0.0 && solutions[1] > 0.0)
        *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
    else  if (solutions[0] < 0.0 && solutions[1] < 0.0)
        return (0);
    else
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