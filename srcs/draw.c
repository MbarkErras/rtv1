#include "../includes/rtv1.h"

t_vec3	ft_pro_k(t_vec3 a, double k)
{
	return (VEC(a.x * k, a.y * k, a.z * k));
}

t_vec3	ft_div_k(t_vec3 a, double k)
{
	return (VEC(a.x / k, a.y / k, a.z / k));
}

t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
	return (VEC((a.y * b.z - a.z * b.y), -(a.x * b.z - a.z * b.x),
				(a.x * b.y - a.y * b.x)));
}

t_vec3	ft_sub(t_vec3 a, t_vec3 b)
{
	return (VEC(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_camera	ft_init_camera(t_vec3 lookfrom, t_vec3 lookat, double vfov)
{
	t_camera	c;
	t_vec3	vup;

	vup = vecnorm(VEC(0.001, 1, 0.001));
	c.half_h = tan((vfov * M_PI / 180.0) / 2.0);
	c.half_w = (WIDTH / HEIGHT) * c.half_h;
	c.origin = lookfrom;
	c.w = vecnorm(ft_sub(lookat, lookfrom));
	c.u = vecnorm(ft_cross(c.w, vup));
	c.v = ft_cross(c.u, c.w);
	c.lower_left_corner = ft_sub(c.origin, vecadd(ft_pro_k(c.v, c.half_h),
				ft_pro_k(c.u, c.half_w)));
	c.lower_left_corner = vecadd(c.lower_left_corner, c.w);
	c.horizontal = ft_pro_k(c.u, 2.0 * c.half_w);
	c.vertical = ft_pro_k(c.v, 2.0 * c.half_h);
	c.fov = vfov;
	c.lookat = lookat;
	return (c);
}

// t_vec3		ft_double_to_color(int i)
// {
// 	t_vec3	c;

// 	c.z = i % 256;
// 	c.y = (i / 256) % 256;
// 	c.x = ((i / 256) / 256) % 256;
// 	return (c);
// }

// t_ray		ft_ray(t_vec3 a, t_vec3 b)
// {
// 	t_ray	r;

// 	r.org = a;
// 	r.dir = b;
// 	return (r);
// }


// t_vec3		ft_ray_tracer(t_scene *scene, position)
// {
// 	t_vec3		c;
// 	t_ray		r;
// 	int			ss;

// 	c = ft_double_to_color(scene->objects->content);
// 	ss = -1;
// 	while (++ss < (int)scene->anti_a)
// 	{
// 		r = ft_get_ray(scene->new_cam, position);
// 		c = vecadd_c(c, ft_raytrace_color(scene, &r, scene->object));
// 	}
// 	c = vecopdiv(c, scene->anti_a);
// 	return (c);
// }

void		ft_mlx_putpixel(t_ptr *p, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH
			&& y >= 0 && y < HEIGHT)
	{
		p->data[y * (int)WIDTH + x] = color;
	}
}

void		ft_calcul(t_ptr *p)
{
	t_vec3		c;
	// t_vec3		position;
	int			color;
	int			col;
	int			row;

	row = HEIGHT + 1;
	while (--row >= 0)
	{
		col = 0;
		while (++col < WIDTH)
		{
			// position = addition(addition(p->scene->new_cam.lower_left_corner, multiplication(rt->cam.u, rt->x * 2 * rt->cam.h / WIDHT)), multiplication(rt->cam.v, rt->y * 2 * rt->cam.h / WIDHT));												//*********************
			//c = ft_ray_tracer(p->scene, position);			//*********************
			color = RGBTOI(RGB(c.x), RGB(c.y), RGB(c.z));
			ft_mlx_putpixel(p, col, HEIGHT - row, color);
		}
	}
}

int			ft_draw(t_ptr *p)
{
	ft_bzero(p->data, WIDTH * HEIGHT * 4);
	//ft_calcul(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	return (1);
}

void	ft_create_window(t_ptr *p)
{
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, "rtv1");
}

void	ft_create_image(t_ptr *p)
{
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	p->data = (int*)mlx_get_data_addr(p->img, &p->bpp, &p->size, &p->endian);
}