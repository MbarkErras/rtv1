/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 23:19:30 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/26 00:27:09 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3		diffuse(t_raytracer *r, t_list *light, double dot)
{
	t_vec3		diff;
	t_vec3		light_color;
	t_vec3		object_color;
	double		intensity;

	light_color = d_to_rgb(TLIST(light, t_object)->scalars[0]);
	object_color = d_to_rgb(r->hit.object->scalars[0]);
	intensity = TLIST(light, t_object)->scalars[1];
	diff.x = dot * object_color.x * light_color.x * intensity / 256.0;
	diff.y = dot * object_color.y * light_color.y * intensity / 256.0;
	diff.z = dot * object_color.z * light_color.z * intensity / 256.0;
	return (diff);
}

static t_vec3		specular(t_raytracer *r, t_list *light, double dot)
{
	t_vec3		spec;
	t_vec3		light_color;
	t_vec3		vector[2];
	double		coef;
	double		intensity;

	light_color = d_to_rgb(TLIST(light, t_object)->scalars[0]);
	vector[0] = vecopx(r->ray.dir, -1.0);
	vector[1] = vecsub(vecopx(r->hit.normal, 2.0 * dot),
			vecnorm(vecsub(TLIST(light, t_object)->vectors[0], r->hit.p)));
	coef = vecdot(vector[1], vector[0]) > 0.0 ?
		pow(vecdot(vector[1], vector[0]), 30.0) : 0.0;
	intensity = TLIST(light, t_object)->scalars[1];
	spec.x = coef * light_color.x * intensity;
	spec.y = coef * light_color.y * intensity;
	spec.z = coef * light_color.z * intensity;
	return (spec);
}

int					hit_light(t_raytracer *r, t_object *light)
{
	t_hit		save;
	t_ray		ray;
	int			ret;

	save = r->hit;
	ray = r->ray;
	ft_bzero(&r->hit, sizeof(t_hit));
	r->ray.org = save.p;
	r->ray.dir = vecsub(light->vectors[0], save.p);
	ret = hit_loop(r, save.object);
	r->hit = save;
	r->ray = ray;
	return (ret);
}

int					color_picker(t_raytracer *r)
{
	t_vec3			rgb;
	t_list			*light;
	double			dot;

	rgb = vecset(0.0, 0.0, 0.0);
	light = r->scene.lights;
	while (light)
	{
		dot = (vecdot(r->hit.normal, vecnorm(vecsub(TLIST(light,
								t_object)->vectors[0], r->hit.p))) > 0.0) ?
			vecdot(r->hit.normal, vecnorm(vecsub(TLIST(light,
								t_object)->vectors[0], r->hit.p))) : 0;
		if (!hit_light(r, light->content))
		{
			rgb = vecadd(rgb, diffuse(r, light, dot));
			rgb = vecadd(rgb, specular(r, light, dot));
		}
		light = light->next;
	}
	rgb.x += 0.2 * (((int)r->hit.object->scalars[0] >> 16) & 0xFF);
	rgb.y += 0.2 * (((int)r->hit.object->scalars[0] >> 8) & 0xFF);
	rgb.z += 0.2 * ((int)r->hit.object->scalars[0] & 0xFF);
	clamping_vector(&rgb);
	return (rgb_to_int(rgb));
}
