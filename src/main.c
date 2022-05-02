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

void	draw_wall_segment(t_data *data, t_dimension_2d *wall_seg)
{
	int	i;

	i = 0;
	while (i < wall_seg->y_min && i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, wall_seg->x_min, i, 0x17202a);
		i++;
	}
	while (i < wall_seg->y_max && i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, wall_seg->x_min, i, 0xb71c1c );
		i++;
	}
	while (i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, wall_seg->x_min, i,  0xf1c40f);
		i++;
	}
}

int	render_frame(void *void_img)
{
	int				i;
	t_data			*data;
	t_dimension_2d	wall_dim;

	i = 0;
	data = void_img;
	while (i < data->camera.win_size.x_max)
	{
		raycast_one_slice(data, i, &wall_dim);
		draw_wall_segment(data, &wall_dim);
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
