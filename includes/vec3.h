#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdio.h>
# include <string.h>

typedef struct  s_vec3
{
    double      x; 
    double      y;   
    double      z;    
}               t_vec3;

# define VEC(a, b, c) (t_vec3){a, b, c}

double                          veclength(t_vec3 vec);
t_vec3                            vecnorm(t_vec3 vec);
double                          vecdot(t_vec3 a, t_vec3 b);
t_vec3                          veccross(t_vec3 a, t_vec3 b);
t_vec3                          vecsub(t_vec3 a, t_vec3 b);
t_vec3                          vecopplus(t_vec3 a, double x);
t_vec3                          vecopdiv(t_vec3 a, double x);
t_vec3                          vecdiv(t_vec3 a, t_vec3 b);
t_vec3                          vecreflect(t_vec3 i, t_vec3 n);
t_vec3                          vecadd(t_vec3 a, t_vec3 b);
t_vec3                          vecprod(t_vec3 a, t_vec3 b);
t_vec3                          vecopx(t_vec3 a, double x);
t_vec3	                        vecset(double x, double y, double z);
int                             veccompare(t_vec3 a, t_vec3 b);

#endif
