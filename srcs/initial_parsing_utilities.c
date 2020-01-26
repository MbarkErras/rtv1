/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parsing_utilities.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:52:44 by merras            #+#    #+#             */
/*   Updated: 2020/01/26 00:47:53 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object		*create_object(t_object o)
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

void			parsing_cleanup(t_scene *s)
{
	free(s->camera);
	list_delete(&s->lights, free);
	list_delete(&s->objects, free);
}

void			scene_object_dispatcher(t_scene_parser *s)
{
	if (!(s->object_type = is_recognized(s->object_name_buffer)))
	{
		parsing_cleanup(s->scene);
		exit(ft_perror(EXEC_NAME, NULL, N_WORD));
	}
	if (s->object_type == CAMERA && s->scene->camera)
	{
		parsing_cleanup(s->scene);
		exit(ft_perror(EXEC_NAME, NULL, P_CAM_DUPLICATE));
	}
	if (s->object_type == CAMERA)
		s->scene->camera = create_object(properties_parser(s));
	else if (s->object_type == LIGHT)
		list_push_back(&s->scene->lights, list_create_node(create_object(
				properties_parser(s)), sizeof(t_object)));
	else
		list_push_back(&s->scene->objects, list_create_node(create_object(
				properties_parser(s)), sizeof(t_object)));
}

static int		scene_parser_loop_read(t_scene_parser *s)
{
	if ((s->read_return = read(s->fd, s->object_name_buffer + ++s->i, 1)) < 0)
	{
		parsing_cleanup(s->scene);
		exit(ft_perror(EXEC_NAME, NULL, P_READ_ERROR));
	}
	if (!s->read_return)
	{
		if (s->i)
		{
			parsing_cleanup(s->scene);
			exit(ft_perror(EXEC_NAME, NULL, P_NOT_COMPLETE));
		}
		else
			return (1);
	}
	return (0);
}

int				scene_parser_loop(t_scene_parser *s)
{
	if (scene_parser_loop_read(s))
		return (1);
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
	if (s->comment_flag && s->object_name_buffer[s->i] == '\n' && (s->i = -1))
		s->comment_flag = 0;
	if (s->comment_flag)
		s->i = -1;
	return (0);
}
