/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 23:19:30 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/23 17:27:29 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <stdio.h>

static int			rgb_to_int(t_vec3 rgb)
{
	int				color;

	color = (((int)rgb.x & 0x0ff) << 16) | (((int)rgb.y & 0x0ff) << 8) |
		((int)rgb.z & 0x0ff);
	return (color);
}

static t_vec3		d_to_rgb(double value)
{
	t_vec3			rgb;

	rgb.x = (((int)value >> 16) & 0xFF);
	rgb.y = (((int)value >> 8) & 0xFF);
	rgb.z = ((int)value & 0xFF);
	return (rgb);
}

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
	diff.y = dot * object_color.y * light_color.y * intensity /256.0;
	diff.z = dot * object_color.z * light_color.z * intensity /25.0;
	return (diff);
}

static t_vec3		specular(t_raytracer *r, t_list *light, t_vec3 direction, double dot)
{
	t_vec3		spec;
	t_vec3		light_color;
	t_vec3		vector1;
	t_vec3		vector2;
	double		coef;
	double		intensity;

	light_color = d_to_rgb(TLIST(light, t_object)->scalars[0]);
	vector1 = vecopx(direction, -1.0);
	vector2 = vecsub(vecopx(r->hit.normal, 2.0 * dot), r->ray.dir);
	coef = vecdot(vector2, vector1) > 0.0 ? pow(vecdot(vector2, vector1), 30.0) : 0.0;
	intensity = TLIST(light, t_object)->scalars[1];
	spec.x = coef * light_color.x * intensity;
	spec.y = coef * light_color.y * intensity;
	spec.z = coef * light_color.z * intensity;
	return (spec);
}

int					color_picker(t_raytracer *r)
{
	t_vec3			rgb;
	t_list			*light;
	t_vec3			direction;
	double			dot;

	rgb = vecset(0.0, 0.0, 0.0);
	light = r->scene.lights;
	direction = r->ray.dir;
	while (light)
	{
		r->ray.org = r->hit.p;
		r->ray.dir = vecnorm(vecsub(TLIST(light, t_object)->vectors[0], r->hit.p));
		dot =  (vecdot(r->hit.normal, r->ray.dir) > 0.0) ? 
				vecdot(r->hit.normal, r->ray.dir) : 0;
		// if (!hit_light(r, light->content))
		// {
			 
			rgb = vecadd(rgb, diffuse(r, light, dot));
		 	rgb = vecadd(rgb, specular(r, light, direction, dot));
		// }
		light = light->next;
	}
	rgb.x += 0.2 * (((int)r->hit.object->scalars[0] >> 16) & 0xFF);
	rgb.y += 0.2 * (((int)r->hit.object->scalars[0] >> 8) & 0xFF);
	rgb.z += 0.2 * ((int)r->hit.object->scalars[0] & 0xFF);
	clamping_vector(&rgb);
	return (rgb_to_int(rgb));
}
