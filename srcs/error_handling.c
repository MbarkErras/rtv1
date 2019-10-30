/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:40:37 by merras            #+#    #+#             */
/*   Updated: 2019/10/30 19:23:18 by merras           ###   ########.fr       */
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
