/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:12:38 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 06:00:22 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

// D E V //
# include <stdio.h>
// // // //

#include "../srcs/vec3.h"

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "centropy.h"
# include "simplist.h"

# define EXEC_NAME "rtv1"
# define WIDTH 500
# define HEIGHT 500
# define VFOV 60 // check for undefined
# define HFOV 60 // check for undefined
# define MAX_OBJECT_NAME_SIZE 8

# define VEC(a, b, c) (t_vec3){a, b, c}
# define RGB(x) (int)(x)
# define RGBTOI(x, y, z) (x * 256 * 256 + y * 256 + z)

typedef struct  s_ray
{
    t_vec3   org;
    t_vec3   dir;
}               t_ray;

typedef struct	s_object
{
	int 		object_type;
	double		vectors[5][3];
	double 		scalars[4];
}				t_object;

typedef struct	s_camera
{
	t_vec3	origin;
	t_vec3	lower_left_corner;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	lookat;
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;
	double		fov;
	double		half_h;
	double		half_w;
}				t_camera;

typedef struct	s_scene
{
	t_object	*camera;
	t_camera	new_cam;
	t_list		*lights;
	t_list		*objects;
	double		anti_a;
}				t_scene;

typedef struct	s_ptr
{
	void		*win;
	void		*mlx;
	void		*img;
	int			*data;
	int			bpp;
	int			size;
	int			endian;
	t_scene		*scene;
}				t_ptr;

void    print_parsing_results(t_scene scene); //DEVVVVVV
/*
** PARSING
*/

typedef struct	s_scene_parser
{
	int 				fd;
	t_scene				*scene;
	char				*properties_buffer;
	char				object_name_buffer[MAX_OBJECT_NAME_SIZE + 2];
	int					property_vcounter[7];
	int					property_scounter[7];
	double				vectors[5][3];
	double				scalars[4];
	int					properties_incrementors[2];
	int					comma_counter;
	int					vectors_scalars_separator;
	int					object_type;
	int					read_return;
	int					comment_flag;
	int					offset;
	int					i;
}				t_scene_parser;

t_object				properties_parser(t_scene_parser *automata);
void					parse_scene(int fd, t_scene *scene);
int						is_recognized(char *word);
int						properties_parser_loop(t_scene_parser *s);
int						scene_parser_loop(t_scene_parser *s);

t_object		*create_object(t_object o);

# define POS 0
# define DIR 1
# define TRA 2
# define ROT 3
# define ANG 4

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4
# define CAMERA 5
# define LIGHT 6

# define VECTORS_INCREMENTOR 0
# define SCALARS_INCREMENTOR 1


/*
** RENDERING
*/

void    render_scene(t_scene scene);

/*
** UTILITY MACROS
*/

# define VECTOR_LENGTH(v) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])


/*
** READING SCENE FILE FLAGS
*/

# define COMMENT 0

# define CAMERA_VCOUNT 2
# define LIGHT_VCOUNT 1
# define SPHERE_VCOUNT 2
# define PLANE_VCOUNT 3
# define CYLINDER_VCOUNT 4
# define CONE_VCOUNT 5

# define CAMERA_SCOUNT 0
# define LIGHT_SCOUNT 2
# define SPHERE_SCOUNT 2
# define PLANE_SCOUNT 1
# define CYLINDER_SCOUNT 2
# define CONE_SCOUNT 1


int				ft_perror(char *command, char *arg, int err);

# define N_SCENE 0
# define F_OPEN 1
# define N_WORD 2
# define N_PROP 3
# define P_MIXED 4
# define P_EXTRA 5
# define P_MISSING 6

# define N_SCENE_T ": no passed scene file."
# define F_OPEN_T ": cannot open scene file: "
# define N_WORD_T ": unrecognized object."
# define N_PROP_T ": unrecognized property value."
# define P_MIXED_T ": mixed properties types."
# define P_EXTRA_T ": extranous properties values."
# define P_MISSING_T ": missing properties."


void	ft_create_window(t_ptr *p);
void	ft_create_image(t_ptr *p);
int			ft_draw(t_ptr *p);
void		ft_calcul(t_ptr *p);
void		ft_mlx_putpixel(t_ptr *p, int x, int y, int color);
t_camera	ft_init_camera(t_vec3 lookfrom, t_vec3 lookat, double vfov);

#endif
