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

void	draw_wall_segment(t_data *data, t_ray *ray)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < ray->y_min_clipped_screen_coordinates && i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, ray->x_clipped_screen_coordinates, i, 0x17202a);
		i++;
	}
//	printf("ymax clipped: %d, max: %d\n", ray->y_max_clipped_screen_coordinates, ray->y_max_screen_coordinates);
	while (i < ray->y_max_clipped_screen_coordinates && i < data->camera.win_size.y_max)
	{
		t_img	*tex = data->map->texture[0];
		int	hw = ray->y_max_screen_coordinates - ray->y_min_screen_coordinates;
		int delta_h_upper = ray->y_min_clipped_screen_coordinates - ray->y_min_screen_coordinates;
		int	ht = ray->y_max_clipped_screen_coordinates - ray->y_min_clipped_screen_coordinates;
		int u = (int)((float)tex->height / (float)ht * ((float)cnt));
		int x = 0;
		unsigned int	colour;
		const char *current;
		current = &tex->data[x * tex->bpp / 8 + tex->width * u * tex->bpp / 8];
		colour = current[0] << 24 | current[1] << 16 | current[2] << 8 | current[3];
		draw_1px_to_img(data, ray->x_clipped_screen_coordinates, i, colour);
		if (ray->x_clipped_screen_coordinates == data->camera.win_size.x_max / 2)
		{
			printf("hw: %d, delta_upper: %d, u: %d, ymin: %d, ymin_clipped: %d, y_maxclipped: %d\n", hw, delta_h_upper, u, ray->y_min_screen_coordinates, ray->y_min_clipped_screen_coordinates, ray->y_max_clipped_screen_coordinates);
		}
		i++;
		cnt++;
	}
	while (i < data->camera.win_size.y_max)
	{
		draw_1px_to_img(data, ray->x_clipped_screen_coordinates, i, 0xf1c40f);
		i++;
	}
}

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
		init_textures(&data);
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
