#include "../inc/cube3d.h"

#ifndef TESTING

void	tear_down_mlx_session(t_data *data)
{
	mlx_loop_end(data->mlx.mlx);
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	free_map(&data->map);
	exit(0);
}

int	render_frame(void *void_img)
{
	int		i;
	t_data	*data;
	t_point	p0;
	t_point	p1;

	i = 0;
	data = void_img;
	ft_bzero(&p0, sizeof(t_point));
	ft_bzero(&p1, sizeof(t_point));
	turn_all_pixels_black(data);
	while (i < data->camera.win_size.x_max)
	{
		calc_column_dimensions(data, i, &p0, &p1);
		draw_line(p0, p1, data, 0xFFFFFF);
		p0.y = 0.;
		draw_line(p0, p1, data, 0xFF00FF);
		i++;
	}
	printf("x: %f, y: %f\n", data->player.pos.mat[0][0], data->player.pos.mat[1][0]);
	mlx_put_image_to_window(\
	data->mlx.mlx, data->mlx.mlx_win, data->mlx.img, 0, 0);
	return (0);
}

int	init_mlx(t_data	*data)
{
	data->mlx.mlx = mlx_init();
	if (! data->mlx.mlx)
		return (1);
	data->mlx.mlx_win = mlx_new_window(\
			data->mlx.mlx, data->camera.win_size.x_max, data->camera.win_size.y_max, "3D");
	if (! data->mlx.mlx_win)
	{
		free(data->mlx.mlx);
		return (1);
	}
	data->mlx.img = mlx_new_image(\
			data->mlx.mlx, data->camera.win_size.x_max, data->camera.win_size.y_max);
	if (! data->mlx.mlx_win)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (1);
	}
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, \
			&data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		ft_bzero(&data, sizeof(t_data));
		data.map = parse_map(argv[1]);
		if (! data.map)
		{
			ft_putendl_fd("error in map", 1);
			return (1);
		}
		data.camera = init_camera();
		data.player = init_player(data.map);
		if (init_mlx(&data))
			return (free_map(&data.map) == NULL);
		ft_putendl_fd("init done", 1);
		render_frame(&data);
		mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &handle_key_press, &data);
		mlx_hook(data.mlx.mlx_win, 3, 1L << 1, &handle_key_release, &data);
		mlx_hook(data.mlx.mlx_win, 33, 1L << 17, red_cross_handler, &data);
		mlx_loop(data.mlx.mlx);
	}
	return (0);
}

#endif
