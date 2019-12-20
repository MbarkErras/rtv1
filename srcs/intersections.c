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

int     hit_sphere(t_object camera, t_object sphere, double ray[3], double *distance)
{
    t_vec3 oc;
    t_vec3 center;
    t_vec3 rayv;
    double a;
    double b;
    double c;
    double delta;
    rayv = vecset(ray[0], ray[1], ray[2]);
    rayv = vecnorm(rayv);
    center = vecset(sphere.vectors[0][0], sphere.vectors[0][1], sphere.vectors[0][2]);
    oc = vecsub(vecset(camera.vectors[0][0], camera.vectors[0][1], camera.vectors[0][2]), center);
    a = vecdot(rayv, rayv);
    b = 2 * vecdot(oc, rayv);
    c = vecdot(oc, oc) - (sphere.scalars[1] * sphere.scalars[1]);
    delta = b * b - 4 * a * c;
    if (delta < 0)
        return (0);
    // double solutions[2] = {((-b - sqrt(delta)) / (2.0 * a)), ((-b + sqrt(delta)) / (2.0 * a))};
    // if (solutions[0] > 0 && solutions[1] > 0)
    //     *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
    // else  if (solutions[0] < 0 && solutions[1] < 0)
    //     return (0);
    // else
    //     *distance = solutions[0] > solutions[1] ? solutions[0] : solutions[1];
    return (1);
}