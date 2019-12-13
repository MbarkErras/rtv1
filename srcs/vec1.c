#include "vec3.h"

double  veclength(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3    vecnorm(t_vec3 a)
{
float k;

	if (a.x == 0.0 && a.y == 0.0 && a.z == 0.0)
		return (VEC(0, 0, 0));
	k = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (vecopx(a, k));
}

double  vecdot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3  veccross(t_vec3 a, t_vec3 b)
{
	t_vec3 v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

t_vec3  vecsub(t_vec3 a, t_vec3 b)
{
	t_vec3  v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}
