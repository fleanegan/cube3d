#include "../inc/cube3d.h"

t_ray	calc_distance_to_nearest_wall(t_data *data, t_matrix *dir)
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
		tmp = calc_distance_to_wall(dir, data, &wall);
		if (tmp.distance < result.distance && tmp.distance > -0.001)
			result = tmp;
		wall.parallel_axis++;
	}
	if (result.distance > FLT_MAX * 0.99)
		result.distance = -1;
	return (result);
}

t_ray	calc_distance_to_wall(t_matrix *dir, t_data *data, t_plane *wall)
{
	t_ray		result;
	int			distance_wall;
	t_matrix	intersection;

	ft_bzero(&result, sizeof(t_ray));
	distance_wall = ((int)(data->player.pos.mat[wall->parallel_axis][0] \
		/ TILE_SIZE)) * TILE_SIZE;
	if (wall->normal_vector.mat[wall->parallel_axis][0] < 0)
		distance_wall += TILE_SIZE;
	while (1)
	{
		intersection = find_intersection_with_wall_candidate(\
						dir, data, wall, distance_wall);
		if (is_dir_parallel_to_obstacle_surface(data, &intersection))
		{
			result.distance = -1;
			return (result);
		}
		update_ray(data, wall, &result, &intersection);
		if (result.object_at_contact != NULL)
			return (result);
		distance_wall -= \
			TILE_SIZE * wall->normal_vector.mat[wall->parallel_axis][0];
	}
}

t_matrix	*get_object_at_contact(\
			t_matrix *intersection, t_data *data, t_plane *wall)
{
	int			x;
	int			y;
	t_matrix	*result;

	result = NULL;
	intersection->mat[wall->parallel_axis][0] -= \
		wall->normal_vector.mat[wall->parallel_axis][0] * 10;
	x = ((int)(intersection->mat[0][0] / TILE_SIZE));
	y = ((int)(intersection->mat[1][0] / TILE_SIZE));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0)
		return (result);
	if (data->map->grid[x][y].mat[2][0] > 0.1)
		result = &data->map->grid[x][y];
	return (result);
}
