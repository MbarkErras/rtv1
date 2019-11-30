/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:20:49 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 04:13:17 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	is_recognized(char *word)
{
	printf("to check: |%s|\n", word);
	if (!ft_strcmp(word, "plane:"))
		return (PLANE);
	if (!ft_strcmp(word, "sphere:"))
		return (SPHERE);
	if (!ft_strcmp(word, "cylinder:"))
		return (CYLINDER);
	if (!ft_strcmp(word, "cone:"))
		return (CONE);
	if (!ft_strcmp(word, "camera:"))
		return (CAMERA);
	if (!ft_strcmp(word, "light:"))
		return (LIGHT);
	return (0);
}
