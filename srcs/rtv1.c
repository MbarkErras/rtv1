/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2019/11/03 06:00:24 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;
	t_ptr	p;

	if (argc != 2)
		return (ft_perror(EXEC_NAME, NULL, N_SCENE));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return(ft_perror(EXEC_NAME, argv[1], F_OPEN));
	scene.camera = NULL;
	scene.lights = NULL;
	scene.objects = NULL;
	parse_scene(fd, &scene);
	print_parsing_results(scene);
	scene.new_cam.origin.x = scene.camera->vectors[0][0];
	scene.new_cam.origin.y = scene.camera->vectors[0][1];
	scene.new_cam.origin.z = scene.camera->vectors[0][2];
	scene.new_cam.origin.x = scene.camera->vectors[0][0];
	scene.new_cam.origin.y = scene.camera->vectors[0][1];
	scene.new_cam.origin.z = scene.camera->vectors[0][2];
	scene.new_cam.lookat.x = scene.camera->vectors[1][0];
	scene.new_cam.lookat.y = scene.camera->vectors[1][1];
	scene.new_cam.lookat.z = scene.camera->vectors[1][2];
	scene.new_cam.fov = 60.0;
	scene.new_cam = ft_init_camera(scene.new_cam.origin, scene.new_cam.lookat, 60.0);
	p.scene = &scene;            

	ft_create_window(&p);
	ft_create_image(&p);
	ft_draw(&p);
	mlx_loop(p.mlx);
	//render_scene(scene);
}

