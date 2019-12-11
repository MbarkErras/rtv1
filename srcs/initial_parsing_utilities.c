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

void    scene_object_dispatcher(t_scene_parser *s)
{
    if (!(s->object_type = is_recognized(s->object_name_buffer)))
		exit(ft_perror(EXEC_NAME, "alo", N_WORD));
	if (s->object_type == CAMERA && s->scene->camera)
		exit(ft_perror(EXEC_NAME, "**", N_WORD)); //error!!!!!!!!!!!!
    if (s->object_type == CAMERA)
		s->scene->camera = create_object(properties_parser(s));
	else if (s->object_type == LIGHT)
		list_push_back(&s->scene->lights, list_create_node(create_object(properties_parser(s)), sizeof(t_object)));
	else
		list_push_back(&s->scene->objects, list_create_node(create_object(properties_parser(s)), sizeof(t_object)));
}

int     scene_parser_loop(t_scene_parser *s)
{
    if ((s->read_return = read(s->fd, s->object_name_buffer + ++s->i, 1)) < 0)
		exit(ft_perror(EXEC_NAME, "??", N_WORD)) ;//read error: do something!!
	if (!s->read_return)
		return(1);//is the file content complete?
	if (!s->i && s->object_name_buffer[s->i] == '#')
		s->comment_flag = 1;
	if (!s->comment_flag && s->object_name_buffer[s->i] == ':')
	{
		scene_object_dispatcher(s);
		bzero(s->object_name_buffer, MAX_OBJECT_NAME_SIZE + 2);
		s->i = -1;
	}
	else if (s->i > MAX_OBJECT_NAME_SIZE)
		exit(ft_perror(EXEC_NAME, "ass", N_WORD));
	if (s->comment_flag && s->object_name_buffer[s->i] == '\n')
		s->comment_flag = 0;
	if (s->comment_flag)
		s->i = -1;
	return (0);
}