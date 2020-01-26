/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 21:30:59 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/25 19:04:49 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*ft_strerror(int err)
{
	if (err == F_OPEN)
		return (F_OPEN_T);
	if (err == N_WORD)
		return (N_WORD_T);
	if (err == N_SCENE)
		return (N_SCENE_T);
	if (err == N_PROP)
		return (N_PROP_T);
	if (err == P_MIXED)
		return (P_MIXED_T);
	if (err == P_EXTRA)
		return (P_EXTRA_T);
	if (err == P_MISSING)
		return (P_MISSING_T);
	if (err == P_CAM_MISSING)
		return (P_CAM_MISSING_T);
	if (err == P_READ_ERROR)
		return (P_READ_ERROR_T);
	if (err == P_CAM_DUPLICATE)
		return (P_CAM_DUPLICATE_T);
	if (err == P_NOT_COMPLETE)
		return (P_NOT_COMPLETE_T);
	if (err == P_LONG)
		return (P_LONG_T);
	return (NULL);
}

int		ft_perror(char *command, char *arg, int err)
{
	if (command)
		ft_putstr_fd(command, 2);
	ft_putstr_fd(ft_strerror(err), 2);
	if (arg)
		ft_putendl_fd(arg, 2);
	else
		ft_putchar_fd('\n', 2);
	return (err);
}

int		is_recognized(char *word)
{
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

int		grammar_checker(char *buffer, int i)
{
	return (
		(!ft_isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\n' &&
			buffer[i] != '.' && buffer[i] != ',' && buffer[i] != '-') ||
		(i && (buffer[i] == '.' || buffer[i] == ',') &&
			!ft_isdigit(buffer[i - 1])) ||
		(i && (buffer[i - 1] == '.' || buffer[i - 1] == ',') &&
			(!ft_isdigit(buffer[i]) && buffer[i] != '-')) ||
		(i && buffer[i] == '-' && buffer[i - 1] != ' ' &&
			buffer[i - 1] != ',') ||
		(i && buffer[i - 1] == '-' && !ft_isdigit(buffer[i])));
}
