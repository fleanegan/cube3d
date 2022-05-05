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

int	render_next_frame(void *data){
	move(data);
	rotate(data);
	render_frame(data);
	update_mouse_gun(data);
	return 1;
	(void) data;
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
		mlx_loop_hook(data.mlx.mlx, render_next_frame, &data);
		mlx_loop(data.mlx.mlx);
	}
	return (0);
}

#endif
