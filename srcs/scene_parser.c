/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:52:44 by merras            #+#    #+#             */
/*   Updated: 2019/10/30 19:23:06 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** comment about parse_properties() first error checking condition.
** first i check if there is any character that doesn't belong to our grammar:
** precisely, any digit, ",", ".", " ".
** after i check that every "," or "." has a digit before and after.
*/

void	parse_properties(int fd, int object_type)
{
	t_object o;
	int		offset;
	int		i;
	int		flag;
	char	b[1000];

	o.type = object_type;
	offset = 0;
	i = -1;
	while (read(fd, b + ++i, 1) > 0)
	{
		if (b[i] == '.')
			flag = 1;
		if (!isdigit(b[i]) || b[i] != ' ' || b[i] != '\n' || b[i] != '.' || 
		((b[i] == '.' || b[i] == ',') && (!i || (!ft_isdigit(b[i - 1]) &&
		!ft_isdigit(b[i + 1])))))
			exit(ft_perror(EXEC_NAME, NULL, N_PROP));
		if (b[i] == ',' || b[i] == '\n')
		{

			offset = i;
		}
		else
			exit(ft_perror(EXEC_NAME, NULL, N_PROP));
			
	
	}

}

void	parse_scene(int fd)
{
	int		i;
	char	flag;
	char	buffer[MAX_OBJECT_NAME_SIZE + 1];

	bzero(buffer, MAX_OBJECT_NAME_SIZE + 1);
	i = -1;
	while (read(fd, buffer + ++i, 1) > 0)
	{
		if (!flag && buffer[i] == ':')
		{
			if (!(flag = is_recognized(buffer)))
				exit(ft_perror(EXEC_NAME, NULL, N_WORD));
			parse_properties(fd, flag);
			bzero(buffer, 10);
			i = -1;
		}
		if (!flag && i > MAX_OBJECT_NAME_SIZE)
			exit(ft_perror(EXEC_NAME, buffer, N_WORD));
		if (buffer[i] == '#' || (buffer == '\n' && flag))
			flag = buffer[i] == '#';
		if (flag)
			i = -1;
	}
}
