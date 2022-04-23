#include "../inc/cube3d.h"

t_matrix linear_function_matrix(t_matrix *dir, const t_matrix *base, t_matrix *result, float t);
float calc_distance_in_one_axis(t_matrix *dir, t_game_obj *game_obj, int normal_of_plane, int axis);

int generate_direction_vector(t_game_obj *game_obj, t_matrix *result)
{
	t_matrix dir_init;

	zero_init_point(result);
	zero_init_point(&dir_init);
	dir_init.mat[0][0] = 1;
	dir_init.mat[1][0] = 0;
	if (multiply(&(*game_obj).orientation, &dir_init, result))
	{
		printf("matrix multiplication failed\n");
		return (1);
	}
	return (0);
}

float	calc_point_distance(t_matrix *from, t_matrix *to)
{
	float	sqrd_d;
	int		i;

	i = 0;
	sqrd_d = 0;
	while (i < 3)
	{
		sqrd_d += powf(from->mat[i][0] - to->mat[i][0], 2.);
		i++;
	}
	return (sqrtf(sqrd_d));
}

int	is_intersection_on_wall(\
	t_matrix *intersection, int normal_direction_plane, int axis, t_game_obj *game_obj)
{
	int	x;
	int y;
	intersection->mat[axis][0] += normal_direction_plane;
	x = ((int) (intersection->mat[0][0] / TILE_SIZE));
	y = ((int) (intersection->mat[1][0] / TILE_SIZE));
	if (game_obj->map->grid[x][y].mat[2][0] > 0.1)
		return (1);
	return (0);
}

float	calc_distance_to_wall(t_matrix *dir, t_game_obj *game_obj)
{
	int normal_direction_plane = -1;
	int axis = 1;

	if (dir->mat[1][0] > 0)
	{
		return (calc_distance_in_one_axis(dir, game_obj, normal_direction_plane, axis));
	}
	else
	{
		puts("unhandled case");
		return (-1.f);
	}
}

float	calc_distance_in_one_axis(\
		t_matrix *dir, t_game_obj *game_obj, int normal_of_plane, int axis)
{
	float		result;
	t_matrix	intersection;
	int			distance_wall;
	float		t;

	zero_init_point(&intersection);
	distance_wall = ((int) (game_obj->pos.mat[axis][0] / TILE_SIZE))* TILE_SIZE;
	while (1)
	{
		t = (distance_wall - game_obj->pos.mat[axis][0]) / (dir->mat[axis][0] * normal_of_plane);
		intersection = linear_function_matrix(dir, &game_obj->pos, &intersection, t);
		result = calc_point_distance(&game_obj->pos, &intersection);
		if (is_intersection_on_wall(&intersection, normal_of_plane, axis, game_obj))
			return (result);
		distance_wall += TILE_SIZE;
	}
}

t_matrix	linear_function_matrix(\
			t_matrix *dir, const t_matrix *base, t_matrix *result, float t)
{
	result->mat[0][0] = base->mat[0][0] + t * dir->mat[0][0];
	result->mat[1][0] = base->mat[1][0] + t * dir->mat[1][0];
	result->mat[2][0] = base->mat[2][0] + t * dir->mat[2][0];
	return (*result);
}
