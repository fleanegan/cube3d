/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:19 by                   #+#    #+#             */
/*   Updated: 2022/02/01 18:16:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_data			*data;

	data = void_img;
	turn_all_pixels_black(data);
	t_point	p0;
	t_point	p1;
	int		i;

	i = 0;
	while (i < data->camera.win_size.x_max)
	{
		calc_column_dimensions(data, i, &p0, &p1);
		draw_line(p0, p1, data);
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
		data.map = parse_map(argv[1]);
		if (! data.map)
		{
			ft_putendl_fd("error in map", 1);
			return (1);
		}
		data.camera = init_camera();
		data.player = init_player(data.map);
		if (init_mlx(&data))
		{
			free_map(&data.map);
			return (1);
		}
		ft_putendl_fd("init done", 1);
		render_frame(&data);
		mlx_key_hook(data.mlx.mlx_win, key_handler, &data);
		mlx_loop(data.mlx.mlx);
	}
	return (0);
}

#endif