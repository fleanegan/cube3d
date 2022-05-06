#include "../inc/cube3d.h"

#ifndef TESTING

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
	draw_map(data);
	mlx_put_image_to_window(\
			data->mlx.mlx, data->mlx.mlx_win, data->mlx.img, 0, 0);
	return (0);
}

#endif

void	draw_wall_segment(t_data *data, t_ray *ray)
{
	int				i;
	int				cnt;
	unsigned int	colour;

	i = 0;
	cnt = 0;
	while (i < ray->y_min_clipped_screen && i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, ray->x_clipped_screen, i, 0xFF2Fa);
		i++;
	}
	while (i < ray->y_max_clipped_screen && i < data->camera.win_size.y_max)
	{
		colour = calc_pixel_colour(data, ray, cnt);
		draw_1px_to_img(data, ray->x_clipped_screen, i, colour);
		i++;
		cnt++;
	}
	while (i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, ray->x_clipped_screen, i, 0xf1c40f);
		i++;
	}
}

void	draw_1px_to_img(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->mlx.addr \
		+ (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
