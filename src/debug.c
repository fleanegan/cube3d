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

void	print_map_infos(t_map *map)
{
	ft_putstr_fd("north : ", 1);
	ft_putendl_fd(map->north_texture, 1);
	ft_putstr_fd("south : ", 1);
	ft_putendl_fd(map->south_texture, 1);
	ft_putstr_fd("west : ", 1);
	ft_putendl_fd(map->west_texture, 1);
	ft_putstr_fd("east : ", 1);
	ft_putendl_fd(map->east_texture, 1);
	ft_putstr_fd("ceilling : ", 1);
	ft_putnbr_fd(map->ceilling_color, 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("floor : ", 1);
	ft_putnbr_fd(map->floor_color, 1);
	ft_putendl_fd("", 1);
}
