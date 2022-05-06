#include "../inc/cube3d.h"

static void		ray_set_wall_orientation(t_plane *wall, t_ray *result);

void	ray_set_wall_orientation(t_plane *wall, t_ray *result)
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

t_matrix	find_intersection_with_wall_candidate(\
				t_matrix *dir, const t_data *data, \
				const t_plane *wall, int distance_wall)
{
	t_matrix	intersection;
	float		t;

	zero_init_point(&intersection);
	t = fabsf((float)(distance_wall \
		- data->player.pos.mat[wall->parallel_axis][0]) \
	/ ((float) fabs(dir->mat[wall->parallel_axis][0] \
	* (float) wall->normal_vector.mat[wall->parallel_axis][0])));
	intersection = find_ray_end(dir, &data->player.pos, &intersection, t);
	return (intersection);
}

void	update_ray(t_data *data, t_plane *wall, \
		t_ray *result, t_matrix *intersection)
{
	result->x_intersection_world = (*intersection).mat[0][0];
	result->y_intersection_world = (*intersection).mat[1][0];
	ray_set_wall_orientation(wall, result);
	result->distance = calc_point_distance(&data->player.pos, intersection);
	result->object_at_contact = get_object_at_contact(intersection, data, wall);
}

int	is_dir_parallel_to_obstacle_surface(t_data *data, t_matrix *intersection)
{
	int	x;
	int	y;

	x = ((int)(intersection->mat[0][0] / TILE_SIZE));
	y = ((int)(intersection->mat[1][0] / TILE_SIZE));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0)
		return (1);
	return (0);
}

t_matrix	find_ray_end(t_matrix *dir, const t_matrix *base, \
			t_matrix *result, float t)
{
	result->mat[0][0] = base->mat[0][0] + t * dir->mat[0][0];
	result->mat[1][0] = base->mat[1][0] + t * dir->mat[1][0];
	result->mat[2][0] = base->mat[2][0];
	return (*result);
}
