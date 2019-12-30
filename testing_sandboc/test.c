#include <stdio.h>

double		ft_atof(char *string);
int	main(int argc, char **argv)
{
	printf("%f\n", ft_atof(argv[1]));
}