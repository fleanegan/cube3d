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

void	tear_down_mlx_session(t_data *img)
{
	mlx_loop_end(img->mlx);
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	free_map(&img->map);
	exit(0);
}

int	render_frame(void *void_img)
{
	t_data			*img;

	img = void_img;
	turn_all_pixels_black(img);
	// exec logic
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

int	init_mlx(t_data	*img)
{
	img->win_size.x_max = 1000;
	img->win_size.y_max = 900;
	img->mlx = mlx_init();
	if (! img->mlx)
		return (1);
	img->mlx_win = mlx_new_window(\
		img->mlx, img->win_size.x_max, img->win_size.y_max, "Fils D'enFer");
	if (! img->mlx_win)
	{
		free(img->mlx);
		return (1);
	}
	img->img = mlx_new_image(\
		img->mlx, img->win_size.x_max, img->win_size.y_max);
	if (! img->mlx_win)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);
		return (1);
	}
	img->addr = mlx_get_data_addr(\
	img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc == 2)
	{
		img.map = parse_map(argv[1]);
		if (! img.map)
		{
			ft_putendl_fd("error in map", 1);
			return (1);
		}
		if (init_mlx(&img))
		{
			free_map(&img.map);
			return (1);
		}
		ft_putendl_fd("init done", 1);
		render_frame(&img);
		mlx_key_hook(img.mlx_win, key_handler, &img);
		mlx_loop(img.mlx);
	}
	return (0);
}

#endif