/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:52:44 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 06:00:14 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int     grammar_checker(char *buffer, int i)
{
    return((!ft_isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '.' && buffer[i] != ',') ||
		(i && (buffer[i] == '.' || buffer[i] == ',') && (!ft_isdigit(buffer[i - 1]))) ||
		(i && ((buffer[i - 1] == '.' || buffer[i - 1] == ',') && !ft_isdigit(buffer[i]))));
}

void    comma_state()
{
    if (flags[COMMA_COUNT] > 1)
				exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
	vectors[p[VECTORS_INCREMENTOR]][flags[COMMA_COUNT]] = ft_atoi(buffer + offset);
	flags[COMMA_COUNT]++;
	offset = i + 1;
}

void    vector_state()
{
    if (!property_vcounter[object_type])
					exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
	vectors[p[VECTORS_INCREMENTOR]][2] = ft_atoi(buffer + offset);
	p[VECTORS_INCREMENTOR]++;
	property_vcounter[object_type]--;
}

void    color_state()
{
    if (!property_scounter[object_type])
					exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
	scalars[p[SCALARS_INCREMENTOR]] = ft_atoi(buffer + offset);
	p[SCALARS_INCREMENTOR]++;
	property_scounter[object_type]--;
	flags[JIDAR_BERLIN] = 1;
}

void    scene_parser_loop()
{
    if ((read_return = read(fd, buffer + ++i, 1)) < 0)
			break ;//read error: do something!!
	if (!read_return && (!i || buffer[i - 1] != '\n'))
		buffer[i] = '\n';
	if (grammar_checker(buffer, i)) // if i == 999
		exit(ft_perror(EXEC_NAME, NULL, N_PROP));
	if (buffer[i] == ',')
		comma_state();
	else if (offset != -1 && (buffer[i] == ' ' || buffer[i] == '\n'))
	{
		if (flags[COMMA_COUNT] == 2)
			vector_state();
		else if (!flags[COMMA_COUNT])
			scalar_state();
		else
			exit(ft_perror(EXEC_NAME, NULL, P_MIXED));
		flags[COMMA_COUNT] = 0;
		offset = -1;
	}
	if (offset == -1 && ft_isdigit(buffer[i]))
		offset = i;
	if (buffer[i] == '\n')
        return (1)
    return (0);
}