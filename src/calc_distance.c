#include "../inc/cube3d.h"

void ray_set_wall_orientation(t_plane *wall, t_ray *result);

void
update_ray(t_data *data, t_plane *wall, t_ray *result, t_matrix *intersection);

t_matrix	*get_object_at_contact(t_matrix *intersection, t_data *data, t_plane *wall)
{
	int			x;
	int			y;
	t_matrix	*result;

	result = NULL;
	intersection->mat[wall->parallel_axis][0] -= wall->normal_vector.mat[wall->parallel_axis][0] * 10;
	x = ((int)(intersection->mat[0][0] / data->map->len_per_unit[wall->parallel_axis]));
	y = ((int)(intersection->mat[1][0] / data->map->len_per_unit[wall->parallel_axis]));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0)
		return (result);
	if (data->map->grid[x][y].mat[2][0] > 0.1)
		result = &data->map->grid[x][y];
	return (result);
}

t_ray calc_distance_to_obstacle(t_data *data, t_matrix *dir)
{
	t_plane		wall;
	t_ray		result;
	t_ray		tmp;

	wall.parallel_axis = 0;
	ft_bzero(&result, sizeof(t_ray));
	result.distance = FLT_MAX;
	while (wall.parallel_axis < 2)
	{
		if (dir->mat[wall.parallel_axis][0] > 0)
			wall.normal_vector.mat[wall.parallel_axis][0] = -1;
		else
			wall.normal_vector.mat[wall.parallel_axis][0] = 1;
		tmp = calc_distance_to_wall_matching_normal_vector(dir, data, &wall);
		if (tmp.distance < result.distance && tmp.distance > -0.001)
			result = tmp;
		wall.parallel_axis++;
	}
	if (result.distance > FLT_MAX * 0.99)
		result.distance = -1;
	return (result);
}

void ray_set_wall_orientation(t_plane *wall, t_ray *result)
{
	if (wall->parallel_axis == 0)
	{
		if (wall->normal_vector.mat[wall->parallel_axis][0] == 1)
			result->wall_orientation = 'E';
		else
			result->wall_orientation = 'W';
	}
	else
	{
		if (wall->normal_vector.mat[wall->parallel_axis][0] == 1)
			result->wall_orientation = 'S';
		else
			result->wall_orientation = 'N';
	}
}

t_ray calc_distance_to_wall_matching_normal_vector(t_matrix *dir, t_data *data,
												   t_plane *wall)
{
	t_ray		result;
	t_matrix	intersection;
	int			distance_wall;
	float		t;

	ft_bzero(&result, sizeof(t_ray));
	zero_init_point(&intersection);
	distance_wall = ((int)(data->player.pos.mat[wall->parallel_axis][0] \
				/ data->map->len_per_unit[wall->parallel_axis])) * data->map->len_per_unit[wall->parallel_axis];
	if (wall->normal_vector.mat[wall->parallel_axis][0] < 0)
		distance_wall += data->map->len_per_unit[wall->parallel_axis];
	while (1)
	{
		t = fabsf((float)(distance_wall - data->player.pos.mat[wall->parallel_axis][0]) \
		/ ((float) fabs(dir->mat[wall->parallel_axis][0] * (float) wall->normal_vector.mat[wall->parallel_axis][0])));
		intersection = find_ray_end(dir, &data->player.pos, &intersection, t);
		if (is_dir_parallel_to_obstacle_surface(data, &intersection))
		{
			result.distance = -1;
			return (result);
		}
		update_ray(data, wall, &result, &intersection);
		if (result.object_at_contact != NULL)
			return (result);
		distance_wall -= data->map->len_per_unit[wall->parallel_axis] * wall->normal_vector.mat[wall->parallel_axis][0];
	}
}

void	update_ray(t_data *data, t_plane *wall, t_ray *result, t_matrix *intersection)
{
	(*result).x_intersection_world_coordinates = (*intersection).mat[0][0];
	(*result).y_intersection_world_coordinates = (*intersection).mat[1][0];
	ray_set_wall_orientation(wall, result);
	(*result).distance = calc_point_distance(&data->player.pos, intersection);
	(*result).object_at_contact = get_object_at_contact(intersection, data, wall);
}

int is_dir_parallel_to_obstacle_surface(t_data *data, t_matrix *intersection)
{
	int	x;
	int	y;

	x = ((int)(intersection->mat[0][0] / TILE_SIZE));
	y = ((int)(intersection->mat[1][0] / TILE_SIZE));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0)
		return (1);
	return (0);
}

t_matrix	find_ray_end(\
		t_matrix *dir, const t_matrix *base, t_matrix *result, float t)
{
	result->mat[0][0] = base->mat[0][0] + t * dir->mat[0][0];
	result->mat[1][0] = base->mat[1][0] + t * dir->mat[1][0];
	result->mat[2][0] = base->mat[2][0];
	return (*result);
}