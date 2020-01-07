/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parsing_utilities.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:52:44 by merras            #+#    #+#             */
/*   Updated: 2020/01/06 18:50:41 by merras           ###   ########.fr       */
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
	while (++i < MAX_VCOUNT)
		object->vectors[i] = o.vectors[i];
	ft_memcpy(object->scalars, o.scalars, sizeof(double[MAX_SCOUNT]));
	return (object);
}

void    scene_object_dispatcher(t_scene_parser *s)
{
    if (!(s->object_type = is_recognized(s->object_name_buffer)))
		exit(ft_perror(EXEC_NAME, NULL, N_WORD));
	if (s->object_type == CAMERA && s->scene->camera)
		exit(ft_perror(EXEC_NAME, NULL, P_CAM_DUPLICATE)); //error!!!!!!!!!!!!
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
	{
		// cleanup
		exit(ft_perror(EXEC_NAME, NULL, N_WORD)) ;
	}
	if (!s->read_return)
	{
		if (s->i != -1)
			return(ft_perror(EXEC_NAME, NULL, P_NOT_COMPLETE));
		else
			return (1);
	}
	if (!s->i && s->object_name_buffer[s->i] == '#')
		s->comment_flag = 1;
	if (!s->comment_flag && s->object_name_buffer[s->i] == ':')
	{
		scene_object_dispatcher(s);
		bzero(s->object_name_buffer, MAX_OBJECT_NAME_SIZE + 2);
		s->i = -1;
	}
	else if (s->i > MAX_OBJECT_NAME_SIZE)
		exit(ft_perror(EXEC_NAME, NULL, N_WORD));
	if (s->comment_flag && s->object_name_buffer[s->i] == '\n')
		s->comment_flag = 0;
	if (s->comment_flag)
		s->i = -1;
	return (0);
}