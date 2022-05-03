#include "../inc/cube3d.h"

int	is_contact(t_matrix *intersection, \
		int normal_direction_plane, int axis, t_data *data)
{
	int	x;
	int	y;

	intersection->mat[axis][0] -= normal_direction_plane * 10;
	x = ((int)(intersection->mat[0][0] / data->map->len_per_unit[axis]));
	y = ((int)(intersection->mat[1][0] / data->map->len_per_unit[axis]));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0)
		return (0);
	if (data->map->grid[x][y].mat[2][0] > 0.1)
		return (1);
	return (0);
}

t_ray calc_distance_to_obstacle(t_data *data, t_matrix *dir)
{
	int			normal_direction_plane;
	int			axis;
	t_ray		result;
	t_ray		tmp;

	axis = 0;
	result.distance = FLT_MAX;
	while (axis < 2)
	{
		if (dir->mat[axis][0] > 0)
			normal_direction_plane = -1;
		else
			normal_direction_plane = 1;
		tmp = calc_distance_to_wall_matching_normal_vector(\
				dir, data, normal_direction_plane, axis);
		if (tmp.distance < result.distance && tmp.distance > -0.001)
			result = tmp;
		axis++;
	}
	if (result.distance > FLT_MAX * 0.99)
		result.distance = -1;
	return (result);
}

t_ray	calc_distance_to_wall_matching_normal_vector(\
		t_matrix *dir, t_data *data, int normal_of_plane, int axis)
{
	t_ray		result;
	t_matrix	intersection;
	int			distance_wall;
	float		t;

	ft_bzero(&result, sizeof(t_ray));
	zero_init_point(&intersection);
	distance_wall = ((int)(data->player.pos.mat[axis][0] \
				/ data->map->len_per_unit[axis])) * data->map->len_per_unit[axis];
	if (normal_of_plane < 0)
		distance_wall += data->map->len_per_unit[axis];
	while (1)
	{
		t = fabsf((float)(distance_wall - data->player.pos.mat[axis][0]) \
		/ ((float) fabs(dir->mat[axis][0] * (float) normal_of_plane)));
		if (is_dir_parallel_to_obstacle_surface(data, axis, t))
		{
			result.distance = -1;
			return (result);
		}
		intersection = find_ray_end(dir, &data->player.pos, &intersection, t);
		result.distance = calc_point_distance(&data->player.pos, &intersection);
		if (is_contact(&intersection, normal_of_plane, axis, data))
			return (result);
		distance_wall -= data->map->len_per_unit[axis] * normal_of_plane;
	}
}

int	is_dir_parallel_to_obstacle_surface(\
		t_data *data, int axis, float t)
{
	return ((axis == 0 && fabsf(t) > \
				(float) 2.f * data->map->width * (float)data->map->len_per_unit[axis]) \
			|| (axis == 1 && fabsf(t) > \
				(float) 2.f * data->map->height * (float)data->map->len_per_unit[axis]));
}

t_matrix	find_ray_end(\
		t_matrix *dir, const t_matrix *base, t_matrix *result, float t)
{
	result->mat[0][0] = base->mat[0][0] + t * dir->mat[0][0];
	result->mat[1][0] = base->mat[1][0] + t * dir->mat[1][0];
	result->mat[2][0] = base->mat[2][0];
	return (*result);
}