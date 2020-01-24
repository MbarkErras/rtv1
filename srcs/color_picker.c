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

static t_vec3		d_to_rgb(double value, double coef)
{
	t_vec3			rgb;

	rgb.x = coef * (((int)value >> 16) & 0xFF);
	rgb.y = coef * (((int)value >> 8) & 0xFF);
	rgb.z = coef * ((int)value & 0xFF);
	return (rgb);
}

static t_vec3		diffuse(t_raytracer *r, t_list *light)
{
	t_vec3			vector;
	double			color;
	t_vec3			light_color;

	color = 0.0;
	vector = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
	if (vecdot(vecnorm(vector), r->hit.normal) > 0.0)
		color = vecdot(vecnorm(vector), r->hit.normal);
	light_color = vecset(0.0, 0.0, 0.0);
	light_color = d_to_rgb(TLIST(light, t_object)->scalars[0], 1.0);
	light_color = vecadd(light_color, d_to_rgb(r->hit.object->scalars[0], color));
	return (vecopx(light_color, TLIST(light,
					t_object)->scalars[1] * 256 / veclength(vector)));
}

static t_vec3		specular(t_raytracer *r, t_list *light)
{
	t_vec3			vector;
	t_vec3			reflect;
	double			color;


	color = 0.0;
	vector = vecsub(TLIST(light, t_object)->vectors[0], r->hit.p);
	reflect = vecnorm(vecreflect(vector, r->hit.normal));
	if (vecdot(reflect, r->ray.dir) > 0.0)
		color += pow(vecdot(reflect, r->hit.normal), 200.0);
	return (vecopx(vecset(color, color, color), 256.0));
}

// int					hit_light(t_raytracer *r, t_object *light)
// {
// 	t_hit save;
// 	int ret;

// 	save = r->hit;
// 	ft_bzero(&r->hit, sizeof(t_hit));
// 	r->ray.org = save.p;
// 	r->ray.dir = vecsub(light->vectors[0], save.p);
// 	ret = hit_loop(r, BIG, save.object);
// 	r->hit = save;
// 	return (ret);
// }

int					color_picker(t_raytracer *r)
{
	t_vec3			rgb;
	t_list			*light;

	rgb = vecset(0.0, 0.0, 0.0);
	light = r->scene.lights;
	while (light)
	{
		// if (!hit_light(r, light->content))
		// {
			rgb = vecadd(rgb, diffuse(r, light));
			rgb = vecadd(rgb, specular(r, light));
		// }
		light = light->next;
	}
	rgb.x += 0.2 * (((int)r->hit.object->scalars[0] >> 16) & 0xFF);
	rgb.y += 0.2 * (((int)r->hit.object->scalars[0] >> 8) & 0xFF);
	rgb.z += 0.2 * ((int)r->hit.object->scalars[0] & 0xFF);
	clamping_vector(&rgb);
	return (rgb_to_int(rgb));
}
