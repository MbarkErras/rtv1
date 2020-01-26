/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2020/01/26 01:10:10 by aait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		clean_up(t_raytracer *r)
{
	parsing_cleanup(&r->scene);
	mlx_destroy_image(r->mlx_pointers[0], r->mlx_pointers[2]);
	exit(0);
}

static int		keys(int key, t_raytracer *r)
{
	if (key == ESC)
	{
		clean_up(r);
		exit(0);
	}
	return (1);
}

int				protect_ranges(t_scene scene)
{
	t_list		*o;

	o = scene.lights;
	while (o)
	{
		if (TLIST(o, t_object)->scalars[1] > 1.00001 ||
			TLIST(o, t_object)->scalars[1] < -0.0001)
			return (1);
		o = o->next;
	}
	o = scene.objects;
	while (o)
	{
		if (TLIST(o, t_object)->scalars[0] < 0.0001 ||
			(TLIST(o, t_object)->scalars[1] < 0.0001 &&
			TLIST(o, t_object)->object_type != CONE))
			return (1);
		o = o->next;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_raytracer	raytracer;

	if (argc != 2)
		return (ft_perror(EXEC_NAME, NULL, N_SCENE));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (ft_perror(EXEC_NAME, argv[1], F_OPEN));
	raytracer.scene = (t_scene){NULL, NULL, NULL};
	parse_scene(fd, &raytracer.scene);
	if (protect_ranges(raytracer.scene))
	{
		ft_putstr("error: nooood t9awed\n");
		parsing_cleanup(&raytracer.scene);
		exit(1);
	}
	render_scene(&raytracer);
	mlx_hook(raytracer.mlx_pointers[1], 17, 0, clean_up, &raytracer);
	mlx_hook(raytracer.mlx_pointers[1], 2, 0, keys, &raytracer);
	mlx_loop(raytracer.mlx_pointers[0]);
}
