/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 21:18:33 by aait-el-          #+#    #+#             */
/*   Updated: 2019/12/24 21:18:36 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3      get_normal(t_raytracer *r)
{
    t_vec3  vec;
    t_vec3  o_c;

    if (r->hit.object->object_type == SPHERE)
        return (vecnorm(vecsub(r->hit.p, r->hit.object->vectors[0])));
    if (r->hit.object->object_type == PLANE)
        return (r->hit.object->vectors[1]);
    o_c = vecsub(r->ray.org, r->hit.object->vectors[0]);

    if (r->hit.object->object_type == CYLINDER)
        return(vecnorm(vecsub(vecsub(r->hit.p, r->hit.object->vectors[0]), 
        vecopx(r->hit.object->vectors[3], vecdot(r->ray.dir, r->hit.object->vectors[3])
		* r->hit.distance + vecdot(o_c, r->hit.object->vectors[3])))));

    vec = vecopx(r->hit.object->vectors[3], vecdot(r->ray.dir, r->hit.object->vectors[3]) * 
        r->hit.distance + vecdot(o_c, r->hit.object->vectors[3]));
    vec = vecopx(vec, 1.0 / pow(cos(r->hit.object->scalars[1]), 2));

    if (r->hit.object->object_type == CONE)
        return(vecnorm(vecsub(vecsub(r->hit.p, r->hit.object->vectors[0]), vec)));
    return (vecset(0.0, 0.0, 0.0));
}

void     hit_objects(t_raytracer *r, t_list *object, double *hit_distance)
{
    if (TLIST(object, t_object)->object_type == SPHERE)
        hit_sphere(r, TLIST(object, t_object), hit_distance);
    if (TLIST(object, t_object)->object_type == PLANE)
        hit_plane(r, TLIST(object, t_object), hit_distance);
    if (TLIST(object, t_object)->object_type == CYLINDER)
        hit_cylinder(r, TLIST(object, t_object), hit_distance);
    if (TLIST(object, t_object)->object_type == CONE)
        hit_cone(r, TLIST(object, t_object), hit_distance);
}

int     hit_loop(t_raytracer *r, double big)
{
    double	    hit_distance;
	t_list		*object;

    r->hit.distance = big;
    hit_distance = big;
	object = r->scene.objects;
    while (object)
    {
        hit_objects(r, object, &hit_distance);
        if (hit_distance < r->hit.distance)
		{
            r->hit.object = TLIST(object, t_object);
            r->hit.distance = hit_distance;
            r->hit.p = vecadd(r->ray.org, vecopx(r->ray.dir, r->hit.distance));
            r->hit.normal = get_normal(r);
        }
        object = object->next;
    }
    return (r->hit.distance == big ? 0 : 1);
}