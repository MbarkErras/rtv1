/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 21:18:33 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/26 20:07:40 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	get_normal_plane(t_raytracer *r)
{
	if (vecdot(r->ray.dir, r->hit.object->vectors[1]) < 0.0)
		return (r->hit.object->vectors[1]);
	return (vecopx(r->hit.object->vectors[1], -1.0));
}

static t_vec3	get_normal(t_raytracer *r)
{
	t_vec3		vec;
	t_vec3		o_c;
	t_vec3		v1;

	if (r->hit.object->object_type == SPHERE)
		return (vecnorm(vecsub(r->hit.p, r->hit.object->vectors[0])));
	if (r->hit.object->object_type == PLANE)
		return (get_normal_plane(r));
	o_c = vecsub(r->ray.org, r->hit.object->vectors[0]);
	v1 = vecnorm(vecsub(vecsub(r->hit.p, r->hit.object->vectors[0]),
		vecopx(r->hit.object->vectors[1], vecdot(r->ray.dir,
		r->hit.object->vectors[1]) * r->hit.distance + vecdot(o_c,
		r->hit.object->vectors[1]))));
	if (r->hit.object->object_type == CYLINDER)
		return (v1);
	vec = vecopx(r->hit.object->vectors[1], vecdot(r->ray.dir,
	r->hit.object->vectors[1]) * r->hit.distance + vecdot(o_c,
	r->hit.object->vectors[1]));
	vec = vecopx(vec, 1.0 + pow(tan(r->hit.object->scalars[1]), 2));
	v1 = vecnorm(vecsub(vecsub(r->hit.p,
		r->hit.object->vectors[0]), vec));
	if (r->hit.object->object_type == CONE)
		return (v1);
	return (vecset(0, 0, 0));
}

static void		hit_objects(t_raytracer *r, t_object *object, double *d)
{
	if (object->object_type == SPHERE)
		hit_sphere(r, object, d);
	if (object->object_type == PLANE)
		hit_plane(r, object, d);
	if (object->object_type == CYLINDER)
		hit_cylinder(r, object, d);
	if (object->object_type == CONE)
		hit_cone(r, object, d);
}

int				hit_loop(t_raytracer *r, t_object *self)
{
	double		hit_distance;
	t_list		*object;

	r->hit.distance = BIG;
	hit_distance = BIG;
	object = r->scene.objects;
	while (object)
	{
		if (self && self == object->content)
		{
			object = object->next;
			continue ;
		}
		hit_objects(r, object->content, &hit_distance);
		if (hit_distance < r->hit.distance)
		{
			r->hit.object = object->content;
			r->hit.distance = hit_distance;
			r->hit.p = vecadd(r->ray.org, vecopx(r->ray.dir, r->hit.distance));
			r->hit.normal = get_normal(r);
		}
		object = object->next;
	}
	return (r->hit.distance == BIG ? 0 : 1);
}
