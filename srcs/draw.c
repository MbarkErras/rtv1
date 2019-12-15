#include "rtv1.h"

t_camera	ft_init_camera(t_vec3 lookfrom, t_vec3 lookat, double vfov)
{
	t_camera	c;
	t_vec3	vup;

	vup = vecnorm(VEC(0.001, 1, 0.001));
	c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
	c.half_w = (WIDTH / HEIGHT) * c.half_h;
	c.origin = lookfrom;
	c.w = vecnorm(vecsub(lookat, lookfrom));
	c.u = vecnorm(veccross(c.w, vup));
	c.v = veccross(c.u, c.w);
	c.lower_left_corner = vecsub(c.origin, vecadd(vecopx(c.v, c.half_h),
				vecopx(c.u, c.half_w)));
	c.lower_left_corner = vecadd(c.lower_left_corner, c.w);
	c.horizontal = vecopx(c.u, 2.0 * c.half_w);
	c.vertical = vecopx(c.v, 2.0 * c.half_h);
	c.fov = vfov;
	c.lookat = lookat;
	return (c);
}

// int     inter(t_ptr *ptr, t_object *object, double *dist)
// {
// 	if (object->object_type == 1)
//     		return (plan_intersection(ptr, object, dist));
// 	else if(object->object_type == 2)
//     		return (sphere_intersection(ptr, object, dist));
//     else if(object->object_type == 3)
//     		return (cylinder_intersection(ptr, object, dist));
//     else
// 			return (cone_intersection(ptr, object, dist));
// }

// t_object   *intersection(t_ptr *ptr, double max)
// {
//   t_object *temp;
//   double   dist;
//   t_object *obj_affich;

//   ptr->scene->t = max;
//   temp = ptr->scene->objects;
//   obj_affich = NULL;
//   while (temp)
//   {
//     if (inter(ptr,temp, &dist))
//     {
//         if (ptr->scene->t > dist)
//         {
//           ptr->scene->t = dist;
//           obj_affich = temp;
//         }
//     }
//     temp = temp->next;
//   }
//     return (obj_affich);
// }

// void		ray_tracer(t_ptr *ptr, t_vec3  position)
// {
// 	t_object	*obj_affich;

// 	ptr->scene->new_cam.lookat = vecnorm(vecsub(position, ptr->scene->new_cam.origin));
// 	obj_affich = intersection(ptr->scene, 800000.0);
// 	if (obj_affich && ptr->scene->t > 0.0)
//   	{
// 		put_pixel(ptr, ptr->scene->x, ptr->scene->y, ray_tracer_color(ptr, obj_affich));
// 	}
// }

// void		ft_calcul(t_ptr *p)
// {
// 	t_vec3		c;
// 	t_vec3		position;
// 	int			color;
// 	int			col;
// 	int			row;

// 	row = HEIGHT + 1;
// 	while (--row >= 0)
// 	{
// 		col = 0;
// 		while (++col < WIDTH)
// 		{
// 			position = vecadd(vecadd(p->scene->new_cam.lower_left_corner, vecopx(p->scene->new_cam.u, p->scene->x * 2 * p->scene->new_cam.half_w / WIDTH)), vecopx(p->scene->new_cam.v, p->scene->y * 2 * p->scene->new_cam.half_h / HEIGHT));												//*********************
// 			ray_tracer(p, position);
// 			ft_mlx_putpixel(p, col, HEIGHT - row, color);
// 		}
// 	}
// }

int			ft_draw(t_ptr *p)
{
	ft_bzero(p->data, WIDTH * HEIGHT * 4);
	//ft_calcul(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	return (1);
}

void		ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH
			&& y >= 0 && y < HEIGHT)
	{
		p->data[y * (int)WIDTH + x] = color;
	}
}

void	ft_create_window(t_ptr *p)
{
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, "ptrv1");
}

void	ft_create_image(t_ptr *p)
{
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, &p->bpp, &p->size, &p->endian);
}