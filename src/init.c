#include "../inc/cube3d.h"

t_player	init_player_pose(t_map *map, t_player *result);

t_player	init_player(t_map *map)
{
	t_player	result;

	ft_bzero(&result, sizeof(t_player));
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

int init_textures(t_data *data)
{
	int		width;
	int		height;

	data->map->mouse_texture = mlx_xpm_file_to_image(data->mlx.mlx, "test/assets/mouse.xpm", &width, &height);
	data->map->texture[0] = mlx_xpm_file_to_image(data->mlx.mlx, "test/assets/t1.xpm", &width, &height);
	data->map->texture[1] = mlx_xpm_file_to_image(data->mlx.mlx, "test/assets/vive_raclette.xpm", &width, &height);
	data->map->texture[2] = mlx_xpm_file_to_image(data->mlx.mlx, "test/assets/metal-cogs-and-gears.xpm", &width, &height);
	data->map->texture[3] = mlx_xpm_file_to_image(data->mlx.mlx, "test/assets/texture.xpm", &width, &height);
	if (data->map->texture[0] || data->map->texture[1] || data->map->texture[2] || data->map->texture[3])
		return (1);
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

t_camera	init_camera(void)
{
	t_camera	result;

	result.win_size.x_max = 800;
	result.win_size.y_max = 600;
	result.angle_camera_horizontal = 60.f;
	result.distance_screen = \
		result.win_size.x_max / 2.f / tanf(result.angle_camera_horizontal / 2.f * DEG2RAD);
	result.angle_camera_vertical = 2 * atan((result.win_size.y_max / 2.f) / result.distance_screen) * 180.f / M_PI;
	printf("screen distance: %f, vertical angle: %f, g/a: %f\n", result.distance_screen, result.angle_camera_vertical, result.win_size.y_max / 2.f / result.distance_screen);
	return (result);
}
