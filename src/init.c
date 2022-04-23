#include "../inc/cube3d.h"

t_game_obj init_player_pose(t_map *map, t_game_obj *result);

t_game_obj	init_game_obj(t_map *map)
{
	t_game_obj	result;
	ft_bzero(&result, sizeof(t_game_obj));
	result = init_player_pose(map, &result);
	return (result);
}

t_game_obj init_player_pose(t_map *map, t_game_obj *result) {
	scalar_multiply(map->spawn_point, TILE_SIZE, &(*result).pos);
	(*result).pos.mat[0][0] += TILE_SIZE * 0.5f;
	(*result).pos.mat[1][0] += TILE_SIZE * 0.5f;
	zero_init_rotation_matrix(&(*result).orientation);
	if (map->spawn_orientation == 'N')
		(*result).orientation = euler2rot(0., 0., 90.);
	else if (map->spawn_orientation == 'S')
		(*result).orientation = euler2rot(0., 0., -90.);
	else if (map->spawn_orientation == 'W')
		(*result).orientation = euler2rot(0., 0., 180.);
	else
		(*result).orientation = euler2rot(0., 0., 0.);
	return (*result);
}
