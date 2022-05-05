#include "../inc/cube3d.h"

void	draw_map(t_data * data);

int	render_frame(void *void_img)
{
	int		i;
	t_data	*data;
	t_ray	ray;

	i = 0;
	data = void_img;
	while (i < data->camera.win_size.x_max)
	{
		raycast_one_slice(data, i, &ray);
		draw_wall_segment(data, &ray);
		i++;
	}
//	printf("x: %f, y: %f\n", data->player.pos.mat[0][0], data->player.pos.mat[1][0]);
//	print_matrix(&data->player.orientation);
	draw_map(data);
	mlx_put_image_to_window(\
			data->mlx.mlx, data->mlx.mlx_win, data->mlx.img, 0, 0);
	return (0);
}

void	draw_wall_segment(t_data *data, t_ray *ray)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < ray->y_min_clipped_screen_coordinates && i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, ray->x_clipped_screen_coordinates, i, 0xFF2Fa);
		i++;
	}
	while (i < ray->y_max_clipped_screen_coordinates && i < data->camera.win_size.y_max)
	{
		unsigned int colour = calc_pixel_colour(data, ray, cnt);
		draw_1px_to_img(data, ray->x_clipped_screen_coordinates, i, colour);
		i++;
		cnt++;
	}
	while (i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, ray->x_clipped_screen_coordinates, i, 0xf1c40f);
		i++;
	}
}

void draw_map(t_data *data)
{
	int	x;
	int	y;
	int y_map;
	int x_map;
	int mini_map_scale = 5;

	y = (data->camera.win_size.y_max - data->map->height * mini_map_scale) ;
	while (y < data->camera.win_size.y_max && y > 0)
	{
		x = 0;
		y_map =  (y - (data->camera.win_size.y_max - data->map->height * mini_map_scale))/mini_map_scale;
		while (x < data->map->width * mini_map_scale)
		{
			x_map = x /mini_map_scale;
			if (data->map->grid[x_map][y_map].mat[2][0] > 0.1)
				draw_1px_to_img(data, x, y, 0xFF);
			else
				draw_1px_to_img(data, x, y, 0x12355);
			int x_own;
			int y_own;
			x_own = (int)(data->player.pos.mat[0][0] / data->map->len_per_unit[0]);
			y_own = (int)(data->player.pos.mat[1][0] / data->map->len_per_unit[0]);
			if (x_own == x_map && y_own == y_map)
				draw_1px_to_img(data, x, y, 0xFFFF);
			x++;
		}
		y++;
	}
}

void	draw_1px_to_img(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->mlx.addr \
		+ (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
