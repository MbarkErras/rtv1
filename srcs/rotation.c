/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:48:30 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/26 01:07:34 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	rotatex(t_vec3 direction, double theta)
{
	t_vec3	new_direction;

	new_direction.x = direction.x;
	new_direction.y = direction.y * cos(theta) - direction.z * sin(theta);
	new_direction.z = direction.y * sin(theta) + direction.z * cos(theta);
	return (new_direction);
}

static t_vec3	rotatey(t_vec3 direction, double theta)
{
	t_vec3	new_direction;

	new_direction.x = direction.x * cos(theta) + direction.z * sin(theta);
	new_direction.y = direction.y;
	new_direction.z = -direction.x * sin(theta) + direction.z * cos(theta);
	return (new_direction);
}

static t_vec3	rotatez(t_vec3 direction, double theta)
{
	t_vec3	new_direction;

	new_direction.x = direction.x * cos(theta) - direction.y * sin(theta);
	new_direction.y = direction.x * sin(theta) + direction.y * cos(theta);
	new_direction.z = direction.z;
	return (new_direction);
}

void			rotate_direction(t_raytracer *r)
{
	TLIST(r->scene.objects, t_object)->vectors[1] =
		rotatex(TLIST(r->scene.objects, t_object)->vectors[1],
				DEG_TO_RAD(TLIST(r->scene.objects, t_object)->vectors[3].x));
	TLIST(r->scene.objects, t_object)->vectors[1] =
		rotatey(TLIST(r->scene.objects, t_object)->vectors[1],
				DEG_TO_RAD(TLIST(r->scene.objects, t_object)->vectors[3].y));
	TLIST(r->scene.objects, t_object)->vectors[1] =
		vecnorm(rotatez(TLIST(r->scene.objects, t_object)->vectors[1],
					DEG_TO_RAD(TLIST(r->scene.objects,
							t_object)->vectors[3].z)));
}
