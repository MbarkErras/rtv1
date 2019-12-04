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

t_object	*package_object_properties(int object_type, int vectors[5][3], int scalars[4])
{
	t_object *object;

	object = NULL;

	return (object);
}

t_object	*parse_properties(int fd, int object_type)
{
	char			buffer[1000];
	int				vectors[5][3];  //should be changed to double
	int				scalars[4];
	int				i;
	int				flags[2];
	char			property_vcounter[7] = {-1, PLANE_VCOUNT, SPHERE_VCOUNT, CYLINDER_VCOUNT, CONE_VCOUNT, CAMERA_VCOUNT, LIGHT_VCOUNT};
	char			property_scounter[7] = {-1, PLANE_SCOUNT, SPHERE_SCOUNT, CYLINDER_SCOUNT, CONE_SCOUNT, CAMERA_SCOUNT, LIGHT_SCOUNT};
	int				p[2];
	int				offset;
	int				read_return;

	ft_bzero(flags, sizeof(flags));
	ft_bzero(p, sizeof(p));
	i = -1;
	offset = -1;
	printf(">> %d\n", flags[COMMA_COUNT]);
	while (1)
	{
		if ((read_return = read(fd, buffer + ++i, 1)) < 0)
			break ;//read error: do something!!
		if (!read_return && (!i || buffer[i - 1] != '\n'))
			buffer[i] = '\n';
		if ((!ft_isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '.' && buffer[i] != ',') ||
		(i && (buffer[i] == '.' || buffer[i] == ',') && (!ft_isdigit(buffer[i - 1]))) ||
		(i && ((buffer[i - 1] == '.' || buffer[i - 1] == ',') && !ft_isdigit(buffer[i])))) // if i == 999
			exit(ft_perror(EXEC_NAME, NULL, N_PROP));
		if (buffer[i] == ',')
		{
			printf(">> %d\n", flags[COMMA_COUNT]);
			if (flags[COMMA_COUNT] > 1)
				exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
			vectors[p[VECTORS_INCREMENTOR]][flags[COMMA_COUNT]] = ft_atoi(buffer + offset);
			flags[COMMA_COUNT]++;
			offset = i + 1;
		}
		else if (offset != -1 && (buffer[i] == ' ' || buffer[i] == '\n'))
		{
			if (flags[COMMA_COUNT] == 2)
			{
				if (!property_vcounter[object_type])
					exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
				vectors[p[VECTORS_INCREMENTOR]][2] = ft_atoi(buffer + offset);
				p[VECTORS_INCREMENTOR]++;
				property_vcounter[object_type]--;
			}
			else if (!flags[COMMA_COUNT])
			{
				if (!property_scounter[object_type])
					exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
				scalars[p[SCALARS_INCREMENTOR]] = ft_atoi(buffer + offset);
				p[SCALARS_INCREMENTOR]++;
				property_scounter[object_type]--;
				flags[JIDAR_BERLIN] = 1;
			}
			else
				exit(ft_perror(EXEC_NAME, NULL, P_MIXED));
			flags[COMMA_COUNT] = 0;
			offset = -1;
		}
		if (offset == -1 && ft_isdigit(buffer[i]))
			offset = i;
		if (buffer[i] == '\n')
			break ;
	}
	if (property_vcounter[object_type] || property_scounter[object_type])
		exit(ft_perror(EXEC_NAME, NULL, P_MISSING));
	return (package_object_properties(object_type, vectors, scalars));
}

t_scene		parse_scene(int fd)
{
	t_list		*objects_list;
	char		buffer[MAX_OBJECT_NAME_SIZE + 2];
	int			comment_flag;
	t_object	*object;
	t_scene		scene;
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
			printf(">> |%s|\n", buffer);
			if (!(object_type = is_recognized(buffer)))
				exit(ft_perror(EXEC_NAME, buffer, N_WORD));
			//check for object type
			//require camera
			list_push_back(&objects_list, list_create_node(create_object(parse_properties(fd, object_type)), sizeof(t_object)));
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
	return (scene);
}

/* to-do list:
	- adjust offsets correctly.
	- manage anomalies: empty lines..
	- norming
*/