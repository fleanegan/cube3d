#include "../inc/cube3d.h"

void	init_points_to_wall(const t_map *map, t_matrix *const *result)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			zero_init_point(&result[x][y]);
			result[x][y].mat[2][0] = 1;
			x++;
		}
		y++;
	}
}
