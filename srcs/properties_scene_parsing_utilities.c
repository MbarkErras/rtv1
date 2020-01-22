/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_scene_parsing_utilities.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:52:44 by merras            #+#    #+#             */
/*   Updated: 2020/01/06 18:50:43 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int     grammar_checker(char *buffer, int i)
{
    return(
		(!ft_isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\n' &&
			buffer[i] != '.' && buffer[i] != ',' && buffer[i] != '-') ||
		(i && (buffer[i] == '.' || buffer[i] == ',') &&
			!ft_isdigit(buffer[i - 1]) ) ||
		(i && (buffer[i - 1] == '.' || buffer[i - 1] == ',') &&
			(!ft_isdigit(buffer[i]) && buffer[i] != '-') ) ||
		(i && buffer[i] == '-' && buffer[i - 1] != ' ' &&
			buffer[i - 1] != ',') ||
		(i && buffer[i - 1] == '-' && !ft_isdigit(buffer[i]))
		);
}

void    scalar_state(char *buffer, t_scene_parser *s)
{
    if (!s->property_scounter[s->object_type])
	{
		parsing_cleanup(s->scene);
		exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
	}
	s->scalars[s->properties_incrementors[SCALARS_INCREMENTOR]] =
		ft_atof(buffer + s->offset, 6);
	s->properties_incrementors[SCALARS_INCREMENTOR]++;
	s->property_scounter[s->object_type]--;
	s->vectors_scalars_separator = 1;
}

void    vector_state(char *buffer, t_scene_parser *s)
{
	(void)buffer;
    if (!s->property_vcounter[s->object_type])
	{
		parsing_cleanup(s->scene);
		exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
	}
	s->vectors[s->properties_incrementors[VECTORS_INCREMENTOR]][2] =
		ft_atof(buffer + s->offset, 6);
	s->properties_incrementors[VECTORS_INCREMENTOR]++;
	s->property_vcounter[s->object_type]--;
}

void    comma_state(char *buffer, t_scene_parser *s)
{
    if (s->comma_counter > 1)
	{
		parsing_cleanup(s->scene);
		exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
	}
	s->vectors[s->properties_incrementors[VECTORS_INCREMENTOR]][s->comma_counter] =
		ft_atof(buffer + s->offset, 6);
	(void)buffer;
	s->comma_counter++;
	s->offset = s->i + 1;
}

// norm this
int    properties_parser_loop(t_scene_parser *s)
{
	int		read_return;

    if (s->i > 998 || (read_return =
		read(s->fd, s->properties_buffer + ++s->i, 1)) < 0)
	{
		parsing_cleanup(s);
		exit(ft_perror(EXEC_NAME, NULL, s->i > 998 ? P_LONG : P_READ_ERROR));
	}
	if (!read_return && (!s->i || s->properties_buffer[s->i - 1] != '\n'))
		s->properties_buffer[s->i] = '\n';
	if (grammar_checker(s->properties_buffer, s->i))
	{
		parsing_cleanup(s);
		exit(ft_perror(EXEC_NAME, NULL, N_PROP));
	}
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
		{
			parsing_cleanup(s->scene);
			exit(ft_perror(EXEC_NAME, NULL, P_MIXED));
		}
		s->comma_counter = 0;
		s->offset = -1;
	}
	if (s->offset == -1 && (ft_isdigit(s->properties_buffer[s->i]) || s->properties_buffer[s->i] == '-'))
		s->offset = s->i;
	if (s->properties_buffer[s->i] == '\n')
       return (1);
    return (0);
}