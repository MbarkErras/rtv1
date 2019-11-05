#include "vec3.h"

double  veclength(t_vec3 *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

void    vecnorm(t_vec3 *vec)
{
	double  n;

	n = 1.0 / sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	vec->x *= n;
	vec->y *= n;
	vec->z *= n;
}

double  vecdot(t_vec3 *a, t_vec3 *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

t_vec3  veccross(t_vec3 *a, t_vec3 *b)
{
	t_vec3 v;

	v.x = a->y * b->z - a->z * b->y;
	v.y = a->z * b->x - a->x * b->z;
	v.z = a->x * b->y - a->y * b->x;
	return (v);
}

t_vec3  vecsub(t_vec3 *a, t_vec3 *b)
{
	t_vec3  v;

	v.x = a->x - b->x;
	v.y = a->y - b->y;
	v.z = a->z - b->z;
	return (v);
}

t_vec3  vecopplus(t_vec3 *a, double x)
{
	t_vec3 v;

	v.x = a->x + x;
	v.y = a->y + x;
	v.z = a->z + x;
	return (v);
}

t_vec3  vecopdiv(t_vec3 *a, double x)
{
	t_vec3 v;

	v.x = a->x / x;
	v.y = a->y / x;
	v.z = a->z / x;
	return (v);
}

t_vec3  vecdiv(t_vec3 *a, t_vec3 *b)
{
	t_vec3  v;

	v.x = a->x / b->x;
	v.y = a->y / b->y;
	v.z = a->z / b->z;
	return (v);
}

t_vec3  vecreflect(t_vec3 *i, t_vec3 *n)
{
	t_vec3  v;

	v.x = i->x - 2.0 * vecdot(n, i) * n->x;
	v.y = i->y - 2.0 * vecdot(n, i) * n->y;
	v.z = i->z - 2.0 * vecdot(n, i) * n->z;
	return (v);
}

/*void    vecclamp(t_vec3 *vec, double a, double b)
  {
  vec->x = ft_clamp(vec->x, a, b);
  vec->y = ft_clamp(vec->y, a, b);
  vec->z = ft_clamp(vec->z, a, b);
  }*/

int		ft_atoi(char *str)
{
	int i;
	int valeur;
	int signe;

	i = 0;
	valeur = 0;
	while ((str[i] == '\n') || (str[i] == ' ') || (str[i] == '\t') ||
			(str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		signe = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((*(str + i) >= '0') && (*(str + i) <= '9'))
	{
		valeur = (valeur * 10) + ((int)*(str + i) - 48);
		i++;
	}
	if (signe == 1)
		return (-valeur);
	return (valeur);
}

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}

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

t_vec3  vecadd(t_vec3 *a, t_vec3 *b)
{
	t_vec3  v;

	v.x = a->x + b->x;
	v.y = a->y + b->y;
	v.z = a->z + b->z;
	return (v);
}

t_vec3  vecprod(t_vec3 *a, t_vec3 *b)
{
	t_vec3  v;

	v.x = a->x * b->x;
	v.y = a->y * b->y;
	v.z = a->z * b->z;
	return (v);
}

t_vec3  vecopx(t_vec3 *a, double x)
{
	t_vec3  v;

	v.x = a->x * x;
	v.y = a->y * x;
	v.z = a->z * x;
	return (v);
}

double  vecdistance(t_vec3 *a, t_vec3 *b)
{
	double  distance;

	distance = sqrt((a->x - b->x) * (a->x - b->x) + \
			(a->y - b->y) * (a->y - b->y) + (a->z - b->z) * (a->z - b->z));
	return (distance);
}


void    init_vec(t_vec3 *v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void    init_ray(t_ray  *r, t_vec3 org, t_vec3 dir)
{
    r->org = org;
    r->dir = dir;
}

t_vec3   color(t_ray   *r)
{
    t_vec3   uni_dir;
    t_vec3   a;
    t_vec3   b;
    t_vec3   c;
    t_vec3   d;
    t_vec3   res;
    double  t;

    init_vec(&a, 1.0, 1.0, 1.0);
    init_vec(&b, 0.5, 0.7, 1.0);
   
    vecnorm(&(r->dir));
    t = 0.5 * ((uni_dir.y) + 1.0);
    c  = vecopx(&a, (1.0 - t));
    d  = vecopx(&b, t);
    res = vecadd(&c, &d);
    return (res);
}

int main()
{
    int nx = 10;
    int ny = 5;
    t_ray   r;
    t_vec3   left;
    t_vec3   hor;
    t_vec3   ver;
    t_vec3   origin;
    t_vec3   col;
    t_vec3   summ;
    t_vec3   summ1;
    t_vec3   s1;
    t_vec3   s2;

    init_vec(&left, -2.0, -1.0, -1.0);
    init_vec(&hor, 4.0, 0.0, 0.0);
    init_vec(&ver, 0.0, 2.0, 0.0);
    init_vec(&origin, 0.0, 0.0, 0.0);

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            double u = (double)i / (double)nx;
            double v = (double)j / (double)ny;
            s1 = vecopx(&hor, u);
            summ = vecadd(&left, &s1);
            s2 = vecopx(&ver, v);
            summ1 = vecadd(&summ, &s2);
            init_ray(&r, origin, summ1);
            col = color(&r);
            int ir = (int)(255.99 * col.x);
            int ig = (int)(255.99 * col.y);
            int ib = (int)(255.99 * col.z);
            printf ("%d %d %d \n", ir, ig, ib);
        }
        printf ("=======================\n");
    }
}
