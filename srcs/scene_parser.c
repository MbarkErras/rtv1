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

void		init_scene_parser(t_scene_parser *p, int object_type)
{
	ft_bzero(p->properties_incrementors, sizeof(p->properties_incrementors));
	p->offset = -1;
	p->i = -1;
}

t_object	package_object_properties(int object_type, int vectors[5][3], int scalars[4])
{
	t_object object;


	return (object);
}

t_object	parse_properties(int fd, int object_type)
{
	t_scene_parser	automata;
	char			buffer[1000];
	int				i;

	init_scene_parse(&automata, object_type);
	while (1)
		if (scene_parser_loop())
			break ;
	if (property_vcounter[object_type] || property_scounter[object_type])
		exit(ft_perror(EXEC_NAME, NULL, P_MISSING));
	return (package_object_properties(object_type,));
}

t_scene		parse_scene(int fd, t_scene *scene)
{
	char		buffer[MAX_OBJECT_NAME_SIZE + 2];
	int			comment_flag;
	t_object	*object;
	int			object_type;
	int			i;
	int			read_return;

	(void)object;
	objects_list = NULL;
	bzero(buffer, MAX_OBJECT_NAME_SIZE + 2);
	comment_flag = 0;
	i = -1;
	while (1)
	{
		if ((read_return = read(fd, buffer + ++i, 1)) < 0)
			break ;//read error: do something!!
		if (!read_return)
			break ;//is the file content complete?
		if (!i && buffer[i] == '#')
			comment_flag = 1;
		if (!comment_flag && buffer[i] == ':')
		{
			if (!(object_type = is_recognized(buffer)))
				exit(ft_perror(EXEC_NAME, buffer, N_WORD));
			if (object_type == CAMERA)
				scene->camera = create_object(parse_properties(fd, object_type));
			if (object_type == CAMERA && scene->camera)
				exit(0); //error!!!!!!!!!!!!
			if (object_type == LIGHT)
				list_push_back(&scene->lights, list_create_node(create_object(parse_properties(fd, object_type)), sizeof(t_object)));
			else
				list_push_back(&scene->objects, list_create_node(create_object(parse_properties(fd, object_type)), sizeof(t_object)));
			bzero(buffer, MAX_OBJECT_NAME_SIZE + 2);
			i = -1;
		}
		else if (i > MAX_OBJECT_NAME_SIZE)
			exit(ft_perror(EXEC_NAME, buffer, N_WORD));
		if (comment_flag && buffer[i] == '\n')
			comment_flag = 0;
		if (comment_flag)
			i = -1;
	}
	if (!scene->camera)
		exit(0); //error!!!!!!!!!!!
	return (scene);
}

/* to-do list:
	- adjust offsets correctly.
	- manage anomalies: empty lines..
	- norming
*/