#include "../inc/cube3d.h"

static int	is_pixel_at_player_pos(const t_data *data, int y_map, int x_map);

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	int		y_map;
	int		x_map;
	float	mini_map_scale;

	mini_map_scale = (data->camera.win_size.y_max * 0.2f) / data->map->height;
	y = (data->camera.win_size.y_max - data->map->height * mini_map_scale) - 1;
	while (++y < data->camera.win_size.y_max && y > 0)
	{
		x = -1;
		y_map = (y - (data->camera.win_size.y_max \
		- data->map->height * mini_map_scale)) / mini_map_scale;
		while (++x < data->map->width * mini_map_scale)
		{
			x_map = x / mini_map_scale;
			if (data->map->grid[x_map][y_map].mat[2][0] > 0.1)
				draw_1px_to_img(data, x, y, 0xFFA07A);
			else
				draw_1px_to_img(data, x, y, 0x00444444);
			if (is_pixel_at_player_pos(data, y_map, x_map))
				draw_1px_to_img(data, x, y, 0x00FF0000);
		}
	}
}

int	is_pixel_at_player_pos(const t_data *data, int y_map, int x_map)
{
	int	x_own;
	int	y_own;

	x_own = (int)(data->player.pos.mat[0][0] / TILE_SIZE);
	y_own = (int)(data->player.pos.mat[1][0] / TILE_SIZE);
	if (x_own == x_map && y_own == y_map)
		return (1);
	return (0);
}
