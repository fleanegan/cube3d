#include "../inc/cube3d.h"

void	init_points_to_wall(const t_map *map, t_matrix *const *result)
{
	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
		{
			zero_init_point(&result[x][y]);
			result[x][y].mat[2][0] = 1;
		}
}