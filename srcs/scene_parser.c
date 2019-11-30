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

/*
void	assign_properties_to_object(t_object *o, int vectors[5][3], int scalars[4])
{
	int	i;

	i = -1;
	while (++i < 5)
		ft_memcpy(o->vectors[i], vectors[i], 3 * sizeof(int));
	ft_memcpy(o->scalars, scalars, 4 * sizeof(int));
	i = -1;
	while (++i < 5)
	{
		if (i == 0)
		{
			if (o->type != PLANE)
				ft_memcpy(o->properties[POS], vectors[i], 3 * sizeof(int));
			else
				ft_memcpy(o->properties[TRA], vectors[i], 3 * sizeof(int));
		}
		if (i == 1)
		{
			if (o->type != SPHERE && o->type != LIGHT)
				ft_memcpy(o->properties[DIR], vectors[i], 3 * sizeof(int));
			if 
		}
		if (i == 2)
		{
			if (o->type == CYLINDER || o->type == CONE)
				ft_memcpy(o->properties[TRA], vectors[i], 3 * sizeof(int));
		}
		if (i == 3)
		{
			if (o->type == CYLINDER || o->type == CONE)
				ft_memcpy(o->properties[ROT], vectors[i], 3 * sizeof(int));
		}
		if (i == 4)
			if (o->type == CONE)
				ft_memcpy(o->properties[ANG], vectors[i], 3 * sizeof(int));
	}
}
*/
/*
** comment about parse_properties() first error checking condition.
** first i check if there is any character that doesn't belong to our grammar:
** precisely, any digit, ",", ".", " ".
** after i check that every "," or "." has a digit before and after.
*/
/*
t_object	parse_properties(int fd, int object_type)
{
	char	property_vcounter[7] = {-1, PLANE_VCOUNT, SPHERE_VCOUNT, CYLINDER_VCOUNT, CONE_VCOUNT, CAMERA_VCOUNT, LIGHT_VCOUNT};
	char	property_scounter[7] = {-1, PLANE_SCOUNT, SPHERE_SCOUNT, CYLINDER_SCOUNT, CONE_SCOUNT, CAMERA_SCOUNT, LIGHT_SCOUNT};
	int			offset;
	int			i;
	t_object	o;
	char		b[1000];
	int			*value_pointer;
	int			vectors[5][3];  //should be changed to double
	int			scalars[4];
	char		flags[8];
	int			p[2];

	ft_bzero(flags, 8);
	ft_bzero(p, 2);
	o.type = object_type;
	offset = -1;
	i = -1;
	//do not forget to set a limit over line
	while (read(fd, b + ++i, 1) > 0)
	{
		if (!ft_isdigit(b[i]) || b[i] != ' ' || b[i] != '\n' || b[i] != '.' || 
		((b[i] == '.' || b[i] == ',') && (!i || (!ft_isdigit(b[i - 1]) &&
		!ft_isdigit(b[i + 1])))))
			exit(ft_perror(EXEC_NAME, NULL, N_PROP));
		if (b[i] == ',')
		{
			if (flags[1] || flags[0] > 1)
				exit(ft_perror(EXEC_NAME, NULL, P_MIXED));
			vectors[p[1]][flags[0]] = atoi(b + offset);
			flags[0]++;
			offset = i + 1;
		}
		if (b[i] == ' ' || b[i] == '\n')
		{
			if (flags[0] == 2)
			{
				if (!property_vcounter[o.type])
					exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
				vectors[p[1]][2] = ft_atoi(b + offset);
				p[1]++;
				property_vcounter[o.type]--;
			}
			else if (!flags[0])
			{
				if (!property_scounter[o.type])
					exit(ft_perror(EXEC_NAME, NULL, P_EXTRA));
				scalars[p[0]] = ft_atoi(b + offset);
				p[0]++;
				property_scounter[o.type]--;
				flags[1] = 1;
			}
			else
				exit(ft_perror(EXEC_NAME, NULL, P_MIXED));
			flags[0] = 0;
			offset = i + 1;
		}
		if (offset == -1 && ft_isdigit(b[i]))
			offset = i;
	}
	if (property_vcounter[o.type] || property_scounter[o.type])
		exit(ft_perror(EXEC_NAME, NULL, P_MISSING));
	assign_properties_to_object(&o, vectors, scalars);
	return (o);
}
*/

#define COMMA_COUNT 0

# define VECTORS_INCREMENTOR 0
# define SCALARS_INCREMENTOR 1
t_object	parse_properties(int fd)
{
	t_object	o;
	char		buffer[1000];
	int			i;
	char		flags[8];
	int			p[2];

	ft_bzero(flags, 8);
	ft_bzero(p, 2);
	i = -1;
	while (read(fd, buffer + ++i, 1) > 0)
	{
		if (!ft_isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '.' ||
		((buffer[i] == '.' || buffer[i] == ',') && (!i || (!ft_isdigit(buffer[i - 1]) && !ft_isdigit(buffer[i + 1]))))) // if i == 999
			exit(ft_perror(EXEC_NAME, NULL, N_PROP));
		
	}
	return (o);
}

t_list		*parse_scene(int fd)
{
	t_list		*objects_list;
	char		buffer[MAX_OBJECT_NAME_SIZE + 1];
	int			comment_flag;
	t_object	object;
	int			i;

	objects_list = NULL;
	bzero(buffer, MAX_OBJECT_NAME_SIZE + 1);
	comment_flag = 0;
	i = -1;
	while (read(fd, buffer + ++i, 1) > 0)
	{
		if (!i && buffer[i] == '#')
			comment_flag = 1;
		if (!comment_flag && buffer[i] == ':')
		{
			if (!is_recognized(buffer))
				exit(ft_perror(EXEC_NAME, buffer, N_WORD));
			object = parse_properties(fd);
			bzero(buffer, 10);
			i = -1;
		}
		else if (i > MAX_OBJECT_NAME_SIZE)
			exit(ft_perror(EXEC_NAME, buffer, N_WORD));
		if (comment_flag && buffer[i] == '\n')
			comment_flag = 0;
		if (comment_flag)
			i = -1;
	}
	return (objects_list);
}