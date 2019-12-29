/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <mbarekerras@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:12:38 by merras            #+#    #+#             */
/*   Updated: 2019/12/29 17:48:49 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "centropy.h"
# include "simplist.h"
# include "rtv1_define.h"
# include "vec3.h"

typedef struct  s_ray
{
    t_vec3   org;
    t_vec3   dir;
}               t_ray;

typedef struct	s_object
{
	int 		object_type;
	double 		scalars[2];
	t_vec3		vectors[5];
}				t_object;

typedef struct	s_scene
{
	t_object	*camera;
	t_list		*lights;
	t_list		*objects;
}				t_scene;

typedef	struct	s_hit
{
	t_object	*object;
	t_vec3		p;
	t_vec3		normal;
	double		distance;
}				t_hit;

typedef struct	s_raytracer
{
	void		*mlx_pointers[3];
	int			*image_data;
	int			mlx_properties[3];
	t_scene		scene;
	t_vec3		plane_vectors[2];
	t_ray		ray;
	t_hit		hit;
	t_vec3		left_corner;
}				t_raytracer;

typedef struct	s_scene_parser
{
	t_scene		*scene;
	double		vectors[4][3];
	double		scalars[2];
	char		object_name_buffer[MAX_OBJECT_NAME_SIZE + 2];
	char		*properties_buffer;
	int			properties_incrementors[2];
	int			vectors_scalars_separator;
	int			property_vcounter[7];
	int			property_scounter[7];
	int			comma_counter;
	int			comment_flag;
	int			object_type;
	int			read_return;
	int			offset;
	int 		fd;
	int			i;
}				t_scene_parser;


t_object		*create_object(t_object o);
t_object		properties_parser(t_scene_parser *automata);
void			parse_scene(int fd, t_scene *scene);
void			parse_scene(int fd, t_scene *scene);
int				ft_perror(char *command, char *arg, int err);
int				is_recognized(char *word);
int				properties_parser_loop(t_scene_parser *s);
int				scene_parser_loop(t_scene_parser *s);

void    		render_scene(t_raytracer *raytracer);

int     		hit_sphere(t_raytracer *r, t_object *object, double *distance);
int     		hit_plane(t_raytracer *r, t_object *object, double *distance);
int     		hit_cylinder(t_raytracer *r, t_object *object, double *distance);
int     		hit_cone(t_raytracer *r, t_object *object, double *distance);
int     		hit_loop(t_raytracer *r, double big);

int     		color_picker(t_raytracer *r);

				//// DEV ///

# include <stdio.h>

void    		print_parsing_results(t_scene scene);

				//// DEV ////

#endif
