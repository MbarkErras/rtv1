/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <mbarekerras@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2019/12/29 18:13:12 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_parse_results(t_scene s)
{
	printf("camera:\n\t(%f, %f, %f)    (%f, %f, %f)    (%f, %f, %f)\n", s.camera->vectors[0].x, s.camera->vectors[0].y, s.camera->vectors[0].z, s.camera->vectors[1].x, s.camera->vectors[1].y, s.camera->vectors[1].z, s.camera->vectors[2].x, s.camera->vectors[2].y, s.camera->vectors[2].z);
	t_list *light = s.lights;
	printf("lights:\n");
	while (light)
	{
		printf("\t(%f, %f, %f)    %f    %f\n", TLIST(light, t_object)->vectors[0].x, TLIST(light, t_object)->vectors[0].y, TLIST(light, t_object)->vectors[0].z, TLIST(light, t_object)->scalars[0], TLIST(light, t_object)->scalars[1]);
		light = light->next;
	}
	t_list *object = s.objects;
	printf("objects:\n");
	while (object)
	{
		printf("\t(%f, %f, %f)    (%f, %f, %f)    (%f, %f, %f)    (%f, %f, %f)    %f    %f\n", TLIST(object, t_object)->vectors[0].x, TLIST(object, t_object)->vectors[0].y, TLIST(object, t_object)->vectors[0].z, TLIST(object, t_object)->vectors[1].x, TLIST(object, t_object)->vectors[1].y, TLIST(object, t_object)->vectors[1].z, TLIST(object, t_object)->vectors[2].x, TLIST(object, t_object)->vectors[2].y, TLIST(object, t_object)->vectors[2].z, TLIST(object, t_object)->vectors[3].x, TLIST(object, t_object)->vectors[3].y, TLIST(object, t_object)->vectors[3].z, TLIST(object, t_object)->scalars[0], TLIST(object, t_object)->scalars[1]);
		object = object->next;
	}
	printf("");
}

int		main(int argc, char **argv)
{
	int			fd;
	t_raytracer	raytracer;

	if (argc != 2)
		return (ft_perror(EXEC_NAME, NULL, N_SCENE));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return(ft_perror(EXEC_NAME, argv[1], F_OPEN));
	raytracer.scene = (t_scene){NULL, NULL, NULL};
	parse_scene(fd, &raytracer.scene);
	print_parse_results(raytracer.scene);
	render_scene(&raytracer);
}
