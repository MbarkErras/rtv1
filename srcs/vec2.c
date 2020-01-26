/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 23:19:30 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/22 20:41:57 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		vecadd(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vec3		vecset(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

int			rgb_to_int(t_vec3 rgb)
{
	int				color;

	color = (((int)rgb.x & 0x0ff) << 16) | (((int)rgb.y & 0x0ff) << 8) |
		((int)rgb.z & 0x0ff);
	return (color);
}

t_vec3		d_to_rgb(double value)
{
	t_vec3			rgb;

	rgb.x = (((int)value >> 16) & 0xFF);
	rgb.y = (((int)value >> 8) & 0xFF);
	rgb.z = ((int)value & 0xFF);
	return (rgb);
}

void		clamping_vector(t_vec3 *rgb)
{
	rgb->x > 255.0 ? rgb->x = 255.0 : 0;
	rgb->y > 255.0 ? rgb->y = 255.0 : 0;
	rgb->z > 255.0 ? rgb->z = 255.0 : 0;
}
