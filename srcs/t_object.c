/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 05:51:49 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 06:00:17 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	*create_object(t_object	o)
{
	t_object	*object;
	int			i;

	object = (t_object *)malloc(sizeof(t_object));
	object->object_type = o.object_type;
	i = -1;
	while (++i < 5)
		ft_memcpy(object->vectors[i], o.vectors[i], 3 * sizeof(int));
	ft_memcpy(object->scalars, o.scalars, 4 * sizeof(int));
	return (object);
}
