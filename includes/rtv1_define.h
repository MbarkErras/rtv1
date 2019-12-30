/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <mbarekerras@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 23:17:18 by aait-el-          #+#    #+#             */
/*   Updated: 2019/12/29 17:11:39 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_DEFINE_H
# define RTV1_DEFINE_H

# define BIG 100000000000.0
# define EXEC_NAME "rtv1"
# define WIDTH 1000
# define HEIGHT 1000
# define VFOV DEG_TO_RAD(60) // check for undefined
# define HFOV DEG_TO_RAD(60) // check for undefined
# define X 0
# define Y 1
# define MAX_OBJECT_NAME_SIZE 8
# define PI 3.14
# define DEG_TO_RAD(x) (x / 180 * PI)
# define PERP_LENGTH 5
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
# define COMMENT 0

# define CAMERA_VCOUNT 3
# define LIGHT_VCOUNT 1
# define SPHERE_VCOUNT 2
# define PLANE_VCOUNT 4
# define CYLINDER_VCOUNT 4
# define CONE_VCOUNT 4
# define CAMERA_SCOUNT 0
# define LIGHT_SCOUNT 2
# define SPHERE_SCOUNT 2
# define PLANE_SCOUNT 1
# define CYLINDER_SCOUNT 2
# define CONE_SCOUNT 2

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