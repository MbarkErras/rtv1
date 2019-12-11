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

void    scalar_state(char *buffer, t_scene_parser *s)
{
    if (!s->property_scounter[s->object_type])
		exit(ft_perror(EXEC_NAME, "alamlik", P_EXTRA));
	s->scalars[s->properties_incrementors[SCALARS_INCREMENTOR]] = ft_atoi(buffer + s->offset);
	s->properties_incrementors[SCALARS_INCREMENTOR]++;
	s->property_scounter[s->object_type]--;
	s->vectors_scalars_separator = 1;
}

void    vector_state(char *buffer, t_scene_parser *s)
{
    if (!s->property_vcounter[s->object_type])
		exit(ft_perror(EXEC_NAME, "lah", P_EXTRA));
	s->vectors[s->properties_incrementors[VECTORS_INCREMENTOR]][2] = ft_atoi(buffer + s->offset);
	s->properties_incrementors[VECTORS_INCREMENTOR]++;
	s->property_vcounter[s->object_type]--;
}


void    comma_state(char *buffer, t_scene_parser *s)
{
    if (s->comma_counter > 1)
		exit(ft_perror(EXEC_NAME, "lwatan", P_EXTRA));
	s->vectors[s->properties_incrementors[VECTORS_INCREMENTOR]][s->comma_counter] = ft_atoi(buffer + s->offset);
	s->comma_counter++;
	s->offset = s->i + 1;
}

int    properties_parser_loop(t_scene_parser *s)
{
	int		read_return;

    if ((read_return = read(s->fd, s->properties_buffer + ++s->i, 1)) < 0)
			exit(0) ;//read error: do something!!
	if (!read_return && (!s->i || s->properties_buffer[s->i - 1] != '\n'))
		s->properties_buffer[s->i] = '\n';
	if (grammar_checker(s->properties_buffer, s->i)) // if i == 999
		exit(ft_perror(EXEC_NAME, ft_itoa(s->i), N_PROP));
	if (s->properties_buffer[s->i] == ',')
		comma_state(s->properties_buffer, s);
	else if (s->offset != -1 &&
			(s->properties_buffer[s->i] == ' ' || s->properties_buffer[s->i] == '\n'))
	{
		if (s->comma_counter == 2)
			vector_state(s->properties_buffer, s);
		else if (!s->comma_counter)
			scalar_state(s->properties_buffer, s);
		else
			exit(ft_perror(EXEC_NAME, NULL, P_MIXED));
		s->comma_counter = 0;
		s->offset = -1;
	}
	if (s->offset == -1 && ft_isdigit(s->properties_buffer[s->i]))
		s->offset = s->i;
	if (s->properties_buffer[s->i] == '\n')
       return (1);
    return (0);
}