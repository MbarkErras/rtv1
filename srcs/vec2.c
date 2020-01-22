/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 23:19:30 by aait-el-          #+#    #+#             */
/*   Updated: 2019/12/24 23:19:32 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3  vecadd(t_vec3 a, t_vec3 b)
{
	t_vec3  v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vec3	vecset(double x, double y, double z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3  vecopx(t_vec3 a, double x)
{
	t_vec3  v;

	v.x = a.x * x;
	v.y = a.y * x;
	v.z = a.z * x;
	return (v);
}

t_vec3  vecreflect(t_vec3 i, t_vec3 n)
{
	t_vec3  v;

	v.x = i.x - 2.0 * vecdot(n, i) * n.x;
	v.y = i.y - 2.0 * vecdot(n, i) * n.y;
	v.z = i.z - 2.0 * vecdot(n, i) * n.z;
	return (v);
}

void     clamping_vector(t_vec3 *rgb)
{
    rgb->x > 255.0 ? rgb->x = 255.0 : 0;
    rgb->y > 255.0 ? rgb->y = 255.0 : 0;
    rgb->z > 255.0 ? rgb->z = 255.0 : 0;
}
