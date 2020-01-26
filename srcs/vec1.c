/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 23:19:30 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/22 20:41:05 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		vecopx(t_vec3 a, double x)
{
	t_vec3	v;

	v.x = a.x * x;
	v.y = a.y * x;
	v.z = a.z * x;
	return (v);
}

double		vecdot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3		vecnorm(t_vec3 a)
{
	double	k;

	if (a.x == 0.0 && a.y == 0.0 && a.z == 0.0)
		return (vecset(0, 0, 0));
	k = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (vecopx(a, k));
}

t_vec3		veccross(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

t_vec3		vecsub(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}
