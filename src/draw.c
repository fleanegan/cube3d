#include "../inc/cube3d.h"

void	draw_1px_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr \
		+ (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	turn_all_pixels_black(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->camera.win_size.x_max)
	{
		y = 0;
		while (y < data->camera.win_size.y_max)
		{
			draw_1px_to_img(data, x, y, 0);
			y++;
		}
		x++;
	}
}
