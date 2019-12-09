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

t_object	package_object_properties(t_scene_parser s)
{
	t_object	object;
	int			i;

	object.object_type = s.object_type;
	i = -1;
	while (++i < 5)
		ft_memcpy(object.vectors[i], s.vectors[i], 3 * sizeof(int));
	ft_memcpy(object.scalars, s.scalars, 4 * sizeof(int)); 
	return (object);
}

void		init_properties_parser(t_scene_parser *p)
{
	p->property_vcounter = (int[7]){-1, PLANE_VCOUNT, SPHERE_VCOUNT, CYLINDER_VCOUNT, CONE_VCOUNT, CAMERA_VCOUNT, LIGHT_VCOUNT};
	p->property_scounter = (int[7]){-1, PLANE_SCOUNT, SPHERE_SCOUNT, CYLINDER_SCOUNT, CONE_SCOUNT, CAMERA_SCOUNT, LIGHT_SCOUNT};
	ft_bzero(p->properties_incrementors, sizeof(p->properties_incrementors));
	p->offset = -1;
	p->i = -1;
}

t_object	properties_parser(t_scene_parser *automata)
{
	init_properties_parser(automata);
	while (1)
		if (properties_parser_loop(automata))
			break ;
	if (automata->property_vcounter[automata->object_type] ||
		automata->property_scounter[automata->object_type])
		exit(ft_perror(EXEC_NAME, NULL, P_MISSING));
	return (package_object_properties(*automata));
}

void    init_scene_parser(int fd, t_scene_parser *automata, t_scene *scene)
{
    automata->fd = fd;
	automata->scene = scene;
    bzero(automata->object_name_buffer, MAX_OBJECT_NAME_SIZE + 2);
    automata->comment_flag = 0;
    automata->i = -1;
}

void	parse_scene(int fd, t_scene *scene)
{
	t_scene_parser	automata;

	init_scene_parser(fd, &automata, scene);
	while (1)
		scene_parser_loop(&automata);
	if (!scene->camera)
		exit(0); //error!!!!!!!!!!!
}

/* to-do list:
	- adjust offsets correctly.
	- manage anomalies: empty lines..
	- norming
*/