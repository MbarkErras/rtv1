/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:52:44 by merras            #+#    #+#             */
/*   Updated: 2020/01/25 23:16:33 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	package_object_properties(t_scene_parser s)
{
	t_object		object;
	int				i;

	object.object_type = s.object_type;
	i = -1;
	while (++i < MAX_VCOUNT)
		object.vectors[i] = vecset(s.vectors[i][0], s.vectors[i][1],
		s.vectors[i][2]);
	ft_memcpy(object.scalars, s.scalars, sizeof(double[MAX_SCOUNT]));
	return (object);
}

void		init_properties_parser(char *buffer, t_scene_parser *p)
{
	ft_memcpy(p->property_vcounter, (int[7]){-1, PLANE_VCOUNT, SPHERE_VCOUNT,
	CYLINDER_VCOUNT, CONE_VCOUNT, CAMERA_VCOUNT, LIGHT_VCOUNT}, sizeof(int[7]));
	ft_memcpy(p->property_scounter, (int[7]){-1, PLANE_SCOUNT, SPHERE_SCOUNT,
	CYLINDER_SCOUNT, CONE_SCOUNT, CAMERA_SCOUNT, LIGHT_SCOUNT}, sizeof(int[7]));
	ft_bzero(p->properties_incrementors, sizeof(int[2]));
	p->properties_buffer = buffer;
	p->offset = -1;
	p->comma_counter = 0;
	p->i = -1;
}

t_object	properties_parser(t_scene_parser *automata)
{
	char			buffer[1000];

	init_properties_parser(buffer, automata);
	while (1)
		if (properties_parser_loop(automata))
			break ;
	if (automata->property_vcounter[automata->object_type] ||
		automata->property_scounter[automata->object_type])
	{
		parsing_cleanup(automata->scene);
		exit(ft_perror(EXEC_NAME, NULL, P_MISSING));
	}
	return (package_object_properties(*automata));
}

void		init_scene_parser(int fd, t_scene_parser *automata, t_scene *scene)
{
	automata->fd = fd;
	automata->scene = scene;
	bzero(automata->object_name_buffer, MAX_OBJECT_NAME_SIZE + 2);
	automata->comment_flag = 0;
	automata->i = -1;
	scene->camera = NULL;
	scene->lights = NULL;
	scene->objects = NULL;
}

void		parse_scene(int fd, t_scene *scene)
{
	t_scene_parser	automata;

	ft_bzero(&automata, sizeof(t_scene_parser));
	init_scene_parser(fd, &automata, scene);
	while (1)
		if (scene_parser_loop(&automata))
			break ;
	if (!scene->camera)
	{
		parsing_cleanup(scene);
		exit(ft_perror(EXEC_NAME, NULL, P_CAM_MISSING));
	}
}
