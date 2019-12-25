#include "../includes/vec3.h"

t_vec3  vecadd(t_vec3 a, t_vec3 b)
{
	t_vec3  v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vec3  vecprod(t_vec3 a, t_vec3 b)
{
	t_vec3  v;

	v.x = a.x * b.x;
	v.y = a.y * b.y;
	v.z = a.z * b.z;
	return (v);
}

t_vec3	vecset(double x, double y, double z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}


t_vec3  vecopx(t_vec3 a, double x)
{
	t_vec3  v;

	v.x = a.x * x;
	v.y = a.y * x;
	v.z = a.z * x;
	return (v);
}
