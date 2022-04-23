#include "../inc/cube3d.h"

t_matrix	find_ray_end(\
			t_matrix *dir, const t_matrix *base, t_matrix *result, float t);
float		calc_distance_to_wall_matching_normal_vector(t_matrix *dir, \
			t_game_obj *game_obj, int normal_of_plane, int axis);
int			is_dir_parallel_to_obstacle_surface(\
			const t_game_obj *game_obj, int axis, float t);

int	is_contact(t_matrix *intersection, \
	int normal_direction_plane, int axis, t_game_obj *game_obj)
{
	int	x;
	int	y;

	if (axis == 2)
		return (1);
	intersection->mat[axis][0] += normal_direction_plane;
	x = ((int)(intersection->mat[0][0] / game_obj->len_per_unit[axis]));
	y = ((int)(intersection->mat[1][0] / game_obj->len_per_unit[axis]));
	if (game_obj->map->grid[x][y].mat[2][0] > 0.1)
		return (1);
	return (0);
}

float	calc_distance_to_obstacle(t_matrix *dir, t_game_obj *game_obj)
{
	int		normal_direction_plane;
	int		axis;
	float	result;
	float	tmp;

	axis = 0;
	result = FLT_MAX;
	while (axis < 3)
	{
		if (dir->mat[axis][0] > 0)
			normal_direction_plane = -1;
		else
			normal_direction_plane = 1;
		tmp = calc_distance_to_wall_matching_normal_vector(\
			dir, game_obj, normal_direction_plane, axis);
		if (tmp < result && tmp > 0.001)
			result = tmp;
		axis++;
	}
	return (result);
}

float	calc_distance_to_wall_matching_normal_vector(\
		t_matrix *dir, t_game_obj *game_obj, int normal_of_plane, int axis)
{
	float		result;
	t_matrix	intersection;
	int			distance_wall;
	float		t;

	zero_init_point(&intersection);
	distance_wall = ((int)(game_obj->pos.mat[axis][0] \
		/ game_obj->len_per_unit[axis])) * game_obj->len_per_unit[axis];
	while (1)
	{
		t = (distance_wall - game_obj->pos.mat[axis][0]) \
			/ (dir->mat[axis][0] * normal_of_plane);
		if (is_dir_parallel_to_obstacle_surface(game_obj, axis, t))
			return (-1);
		intersection = find_ray_end(dir, &game_obj->pos, &intersection, t);
		result = calc_point_distance(&game_obj->pos, &intersection);
		if (is_contact(&intersection, normal_of_plane, axis, game_obj))
			return (result);
		distance_wall += game_obj->len_per_unit[axis];
	}
}

int	is_dir_parallel_to_obstacle_surface(\
		const t_game_obj *game_obj, int axis, float t)
{
	return ((axis == 0 && fabsf(t) > \
				game_obj->map->width * game_obj->len_per_unit[axis]) \
			|| (axis == 1 && fabsf(t) > \
				game_obj->map->height * game_obj->len_per_unit[axis]));
}

t_matrix	find_ray_end(\
			t_matrix *dir, const t_matrix *base, t_matrix *result, float t)
{
	result->mat[0][0] = base->mat[0][0] + t * dir->mat[0][0];
	result->mat[1][0] = base->mat[1][0] + t * dir->mat[1][0];
	result->mat[2][0] = base->mat[2][0] + t * dir->mat[2][0];
	return (*result);
}
