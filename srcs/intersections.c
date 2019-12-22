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

int     hit_sphere(t_object camera, t_object sphere, double ray[3], double *distance, int x, int y)
{
    t_vec3 oc;
    t_vec3 center;
    t_vec3 rayv;
    double a;
    double b;
    double c;
    double delta;

          if (x == 750 && y == 500)
            printf("*nn** test\n");
    rayv = vecset(ray[0], ray[1], ray[2]);
    rayv = vecnorm(rayv);
    center = vecset(sphere.vectors[0][0], sphere.vectors[0][1], sphere.vectors[0][2]);
    oc = vecsub(vecset(camera.vectors[0][0], camera.vectors[0][1], camera.vectors[0][2]), center);
    a = vecdot(rayv, rayv);
    b = 2.0 * vecdot(oc, rayv);
    c = vecdot(oc, oc) - (sphere.scalars[1] * sphere.scalars[1]);
    delta = b * b - 4.0 * a * c;
    if (delta < 0.0)
    {
        if (x == 750 && y == 500)
            printf("*1*\n");
        //printf("\tn/a*\n");
        return (0);
    }
    double solutions[2] = {((-b - sqrt(delta)) / (2.0 * a)), ((-b + sqrt(delta)) / (2.0 * a))};
    if (solutions[0] > 0.0 && solutions[1] > 0.0)
    {

        *distance = solutions[0] < solutions[1] ? solutions[0] : solutions[1];
        if (x == 750 && y == 500)
            printf("*%f*\n", *distance);
        ////printf("\t%f*\n", *distance);
    }
    else  if (solutions[0] < 0.0 && solutions[1] < 0.0)
    {
        if (x == 750 && y == 500)
            printf("*2*\n");
        //printf("\tn/a-\n");
        return (0);
    }
    else
    {
                if (x == 750 && y == 500)
            printf("*3*\n");
        *distance = solutions[0] > solutions[1] ? solutions[0] : solutions[1];
        //printf("\t%f-\n", *distance);
    }
            if (x == 750 && y == 500)
            printf("*5*\n");
    return (1);
}