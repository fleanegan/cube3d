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

void	print_grid(t_matrix **m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			printf("%f ", m[i][j].mat[1][0]);
			j++;
		}
		i++;
	}

}

void	print_map_infos(t_map *map)
{
	if (map == NULL)
		return ;
	ft_putendl_fd("\n---------------------------------------------------", 1);
	ft_putendl_fd("Maps infos :\n", 1);
	ft_putstr_fd("north : ", 1);
	ft_putendl_fd(map->texture[TEXTURE_NO], 1);
	ft_putstr_fd("south : ", 1);
	ft_putendl_fd(map->texture[TEXTURE_SO], 1);
	ft_putstr_fd("west : ", 1);
	ft_putendl_fd(map->texture[TEXTURE_WE], 1);
	ft_putstr_fd("east : ", 1);
	ft_putendl_fd(map->texture[TEXTURE_EA], 1);
	ft_putstr_fd("ceilling : ", 1);
	ft_putnbr_fd(map->ceilling_color, 1);
	ft_putstr_fd("\nfloor : ", 1);
	ft_putnbr_fd(map->floor_color, 1);
	ft_putstr_fd("\nheight : ", 1);
	ft_putnbr_fd(map->height, 1);
	ft_putstr_fd("\nwidth : ", 1);
	ft_putnbr_fd(map->width, 1);
//	print_grid(map->grid);
	ft_putendl_fd("\n---------------------------------------------------\n", 1);
}
