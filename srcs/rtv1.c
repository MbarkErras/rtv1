/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <mbarekerras@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:33:18 by merras            #+#    #+#             */
/*   Updated: 2019/12/29 16:22:37 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	render_scene(&raytracer);
}
