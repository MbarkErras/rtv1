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

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "centropy.h"
# include "simplist.h"

char	property_vcounter[7] = {-1, PLANE_VCOUNT, SPHERE_VCOUNT, CYLINDER_VCOUNT, CONE_VCOUNT, CAMERA_VCOUNT, LIGHT_VCOUNT};
char	property_scounter[7] = {-1, PLANE_SCOUNT, SPHERE_SCOUNT, CYLINDER_SCOUNT, CONE_SCOUNT, CAMERA_SCOUNT, LIGHT_SCOUNT};

# define EXEC_NAME "rtv1"
# define WIDTH 500;
# define HEIGHT 500;
# define VFOV 60; // check for undefined
# define HFOV 60; // check for undefined
# define MAX_OBJECT_NAME_SIZE 8

typedef struct	s_scene_parser
{
	double				vectors[5][3];
	double				scalars[4];
	int					properties_incrementors[2];
	int					comma_counter;
	int					vectors_scalars_separator;
	int					object_type;
	int					offset;
	int					i;
}				t_scene_parser;

typedef struct	s_object
{
	int 		type;
	int			vectors[5][3];
	int 		scalars[4];
}				t_object;

typedef struct	s_scene
{
	t_object	*camera;
	t_list		*lights;
	t_list		*objects;
}				t_scene;

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

#define COMMA_COUNT 0
#define JIDAR_BERLIN 1
# define VECTORS_INCREMENTOR 0
# define SCALARS_INCREMENTOR 1

t_scene			parse_scene(int fd);
int				is_recognized(char *word);

/*
** UTILITY MACROS
*/

# define VECTOR_LENGTH(v) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])

/*
** RENDERING
*/
cam
void    render_object();

/*
** READING SCENE FILE FLAGS
*/

# define COMMENT 0

# define CAMERA_VCOUNT 2
# define LIGHT_VCOUNT 1
# define SPHERE_VCOUNT 2
# define PLANE_VCOUNT 4
# define CYLINDER_VCOUNT 4
# define CONE_VCOUNT 5

# define CAMERA_SCOUNT 0
# define LIGHT_SCOUNT 1
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

#endif
