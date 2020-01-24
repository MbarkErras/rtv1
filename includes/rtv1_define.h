/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 23:17:18 by aait-el-          #+#    #+#             */
/*   Updated: 2020/01/22 18:56:43 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# define ESC 53
# define EXEC_NAME "rtv1"
# define WIDTH 800
# define HEIGHT 800

# define X 0
# define Y 1
# define Z 2

# define MAX_OBJECT_NAME_SIZE 8

# define VECTORS_INCREMENTOR 0
# define SCALARS_INCREMENTOR 1
# define COMMENT 0

# define CAMERA 5
# define CAMERA_VCOUNT 3
# define CAMERA_SCOUNT 0

# define LIGHT 6
# define LIGHT_VCOUNT 1
# define LIGHT_SCOUNT 2

# define SPHERE 2
# define SPHERE_VCOUNT 2
# define SPHERE_SCOUNT 2

# define PLANE 1
# define PLANE_VCOUNT 4
# define PLANE_SCOUNT 1

# define CYLINDER 3
# define CYLINDER_VCOUNT 4
# define CYLINDER_SCOUNT 2

# define CONE 4
# define CONE_VCOUNT 4
# define CONE_SCOUNT 2

# define MAX_VCOUNT 4
# define MAX_SCOUNT 2

# define PI 3.14
# define DEG_TO_RAD(x) (x / 180 * PI)
# define BIG 100000000000.0

# define A 0
# define B 1
# define C 2
# define DELTA 3

# define N_SCENE 0
# define F_OPEN 1
# define N_WORD 2
# define N_PROP 3
# define P_MIXED 4
# define P_EXTRA 5
# define P_MISSING 6
# define P_CAM_MISSING 7
# define P_READ_ERROR 8
# define P_CAM_DUPLICATE 9
# define P_NOT_COMPLETE 10
# define P_LONG 11

# define N_SCENE_T ": no passed scene file."
# define F_OPEN_T ": cannot open scene file: "
# define N_WORD_T ": unrecognized object."
# define N_PROP_T ": unrecognized property value."
# define P_MIXED_T ": mixed properties types."
# define P_EXTRA_T ": extranous properties values."
# define P_MISSING_T ": missing properties."
# define P_CAM_MISSING_T ": missing camera object."
# define P_READ_ERROR_T ": error occured while processing scene file."
# define P_CAM_DUPLICATE_T ": multiple cameras."
# define P_NOT_COMPLETE_T ": scene file is not complete."
# define P_LONG_T ": properties input is too long."
#endif
