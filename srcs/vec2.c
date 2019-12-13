#include "vec3.h"

t_vec3  vecopplus(t_vec3 a, double x)
{
	t_vec3 v;

	v.x = a.x + x;
	v.y = a.y + x;
	v.z = a.z + x;
	return (v);
}

t_vec3  vecopdiv(t_vec3 a, double x)
{
	t_vec3 v;

	v.x = a.x / x;
	v.y = a.y / x;
	v.z = a.z / x;
	return (v);
}

t_vec3  vecdiv(t_vec3 a, t_vec3 b)
{
	t_vec3  v;

	v.x = a.x / b.x;
	v.y = a.y / b.y;
	v.z = a.z / b.z;
	return (v);
}

t_vec3  vecreflect(t_vec3 i, t_vec3 n)
{
	t_vec3  v;

	v.x = i.x - 2.0 * vecdot(n, i) * n.x;
	v.y = i.y - 2.0 * vecdot(n, i) * n.y;
	v.z = i.z - 2.0 * vecdot(n, i) * n.z;
	return (v);
}

/*void    vecclamp(t_vec3 *vec, double a, double b)
  {
  vec.x = ft_clamp(vec.x, a, b);
  vec.y = ft_clamp(vec.y, a, b);
  vec.z = ft_clamp(vec.z, a, b);
  }*/

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	return (res + ((res > 0) ? res2 : -res2));
}
