#include <stdlib.h>
#include <limits.h>
#include "../inc/cube3d.h"

void	print_coordinates(t_point *pt)
{
	ft_putstr_fd("x: ", 1);
	ft_putnbr_fd((int)pt->x, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("y: ", 1);
	ft_putnbr_fd((int)pt->y, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("z: ", 1);
	ft_putnbr_fd((int)pt->z, 1);
	ft_putstr_fd("\n", 1);
}

void print_matrix(t_matrix *a)
{
	int					x;
	int					y;

	y = 0;
	printf("height %d width %d\n", a->height, a->width);
	while (y < a->height)
	{
		x = 0;
		while (x < a->width)
		{
			printf("%f ", a->mat[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}



char * int2bin(int i)
{
	size_t bits = sizeof(int) * CHAR_BIT;

	char * str = malloc(bits + 1);
	if(!str) return NULL;
	str[bits] = 0;

	// type punning because signed shift is implementation-defined
	unsigned u = *(unsigned *)&i;
	for(; bits--; u >>= 1)
		str[bits] = u & 1 ? '1' : '0';

	return str;
}