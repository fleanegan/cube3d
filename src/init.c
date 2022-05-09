/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:02:29 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:02:30 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

t_player	init_player_pose(t_map *map, t_player *result);

t_player	init_player(t_map *map)
{
	t_player	result;

	ft_bzero(&result, sizeof(t_player));
	zero_init_point(&result.pos);
	result = init_player_pose(map, &result);
	return (result);
}

t_player	init_player_pose(t_map *map, t_player *result)
{
	scalar_multiply(map->spawn_point, TILE_SIZE, &(*result).pos);
	(*result).pos.mat[0][0] += TILE_SIZE * 0.5f;
	(*result).pos.mat[1][0] += TILE_SIZE * 0.5f;
	(*result).pos.mat[2][0] = TILE_SIZE * 0.5f;
	zero_init_rotation_matrix(&(*result).orientation);
	if (map->spawn_orientation == 'N')
		(*result).orientation = euler2rot(0., 0., -90.);
	else if (map->spawn_orientation == 'S')
		(*result).orientation = euler2rot(0., 0., 90.);
	else if (map->spawn_orientation == 'W')
		(*result).orientation = euler2rot(0., 0., 180.);
	else
		(*result).orientation = euler2rot(0., 0., 0.);
	return (*result);
}

#ifndef TESTING

int	init_textures(t_data *data)
{
	int		width;
	int		height;

	data->map->mouse_texture = mlx_xpm_file_to_image(data->mlx.mlx, \
	"test/assets/mt.xpm", &width, &height);
	data->map->texture[0] = mlx_xpm_file_to_image(data->mlx.mlx, \
	data->map->texture_name[0], &width, &height);
	data->map->texture[1] = mlx_xpm_file_to_image(data->mlx.mlx, \
	data->map->texture_name[1], &width, &height);
	data->map->texture[2] = mlx_xpm_file_to_image(data->mlx.mlx, \
	data->map->texture_name[2], &width, &height);
	data->map->texture[3] = mlx_xpm_file_to_image(data->mlx.mlx, \
	data->map->texture_name[3], &width, &height);
	if (data->map->texture[0] && data->map->texture[1] && \
		data->map->texture[2] && data->map->texture[3] \
	&& data->map->mouse_texture)
		return (0);
	ft_putendl_fd("Error\nInit of textures failed", 2);
	return (1);
}

int	init_mlx(t_data	*d)
{
	d->mlx.mlx = mlx_init();
	if (! d->mlx.mlx)
		return (1);
	d->mlx.mlx_win = mlx_new_window(\
			d->mlx.mlx, d->camera.win_size.x_max, d->camera.win_size.y_max, "");
	if (! d->mlx.mlx_win)
	{
		free(d->mlx.mlx);
		return (1);
	}
	d->mlx.img = mlx_new_image(\
			d->mlx.mlx, d->camera.win_size.x_max, d->camera.win_size.y_max);
	if (! d->mlx.mlx_win)
	{
		mlx_destroy_window(d->mlx.mlx, d->mlx.mlx_win);
		mlx_destroy_display(d->mlx.mlx);
		free(d->mlx.mlx);
		return (1);
	}
	d->mlx.addr = mlx_get_data_addr(d->mlx.img, \
			&d->mlx.bits_per_pixel, &d->mlx.line_length, &d->mlx.endian);
	return (0);
}
#endif

t_camera	init_camera(void)
{
	t_camera	result;

	result.win_size.x_max = 1000;
	result.win_size.y_max = 800;
	result.angle_camera_horiz = 60.f;
	result.distance_screen = \
		result.win_size.x_max / 2.f \
		/ tanf(result.angle_camera_horiz / 2.f * DEG2RAD);
	result.angle_camera_vertical = 2.f * atanf((result.win_size.y_max / 2.f) \
		/ result.distance_screen) * 180.f / M_PI;
	return (result);
}
