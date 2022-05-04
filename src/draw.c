#include "../inc/cube3d.h"

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
	printf("x: %f, y: %f\n", data->player.pos.mat[0][0], data->player.pos.mat[1][0]);
	print_matrix(&data->player.orientation);
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
