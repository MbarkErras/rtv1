/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:12:38 by merras            #+#    #+#             */
/*   Updated: 2019/10/30 19:23:27 by merras           ###   ########.fr       */
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
# include "centropy.h"
# include "simplist.h"
# include "mlx.h"

# define EXEC_NAME "rtv1"
# define MAX_OBJECT_NAME_SIZE 8

typedef struct	s_object
{
	char		type;
	float		position[3];
	float		direction[3];
	float		translation[3];
	float		rotation[3];
	float		properties[4];
}				t_object;

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4
# define CAMERA 5
# define LIGHT 6

void			parse_scene(int fd);
int				is_recognized(char *word);

/*
** READING SCENE FILE FLAGS
*/

# define COMMENT 0

int				ft_perror(char *command, char *arg, int err);

# define N_SCENE 0
# define F_OPEN 1
# define N_WORD 2
# define N_PROP_T

# define N_SCENE_T ": no passed scene file."
# define F_OPEN_T ": cannot open scene file: "
# define N_WORD_T ": unrecognized object."
# define N_PROP_T ": unrecognized property value."


#endif
