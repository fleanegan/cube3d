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
