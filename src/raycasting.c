#include "../inc/cube3d.h"

t_matrix	find_ray_end(\
			t_matrix *dir, const t_matrix *base, t_matrix *result, float t);
float		calc_distance_to_wall_matching_normal_vector(t_matrix *dir, \
			t_data *data, int normal_of_plane, int axis);
int			is_dir_parallel_to_obstacle_surface(\
			t_data *data, int axis, float t);

int	is_contact(t_matrix *intersection, \
	int normal_direction_plane, int axis, t_data *data)
{
	int	x;
	int	y;

	if (axis == 2)
		return (1);
	intersection->mat[axis][0] -= normal_direction_plane;
	x = ((int)(intersection->mat[0][0] / data->map->len_per_unit[axis]));
	y = ((int)(intersection->mat[1][0] / data->map->len_per_unit[axis]));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0)
		return (0);
	if (data->map->grid[x][y].mat[2][0] > 0.1)
		return (1);
	return (0);
}

float calc_distance_to_obstacle(t_data *data, t_matrix *dir)
{
	int			normal_direction_plane;
	int			axis;
	float		result;
	float		tmp;

	axis = 0;
	result = FLT_MAX;
	while (axis < 3)
	{
		if (dir->mat[axis][0] > 0)
			normal_direction_plane = -1;
		else
			normal_direction_plane = 1;
		tmp = calc_distance_to_wall_matching_normal_vector(\
			dir, data, normal_direction_plane, axis);
		if (tmp < result && tmp > 1.001)
			result = tmp;
		axis++;
	}
	return (result);
}

float	calc_distance_to_wall_matching_normal_vector(\
		t_matrix *dir, t_data *data, int normal_of_plane, int axis)
{
	float		result;
	t_matrix	intersection;
	int			distance_wall;
	float		t;

	zero_init_point(&intersection);
	distance_wall = ((int)(data->player.pos.mat[axis][0] \
		/ data->map->len_per_unit[axis])) * data->map->len_per_unit[axis];
	if (normal_of_plane < 0)
		distance_wall += data->map->len_per_unit[axis];
	while (1)
	{
		t = fabs((double)(distance_wall - data->player.pos.mat[axis][0]) \
 			/ (dir->mat[axis][0] * normal_of_plane));
		if (is_dir_parallel_to_obstacle_surface(data, axis, t))
			return (-1);
		intersection = find_ray_end(dir, &data->player.pos, &intersection, t);
		result = calc_point_distance(&data->player.pos, &intersection);
		if (is_contact(&intersection, normal_of_plane, axis, data))
			return (result);
		distance_wall -= data->map->len_per_unit[axis] * normal_of_plane;
	}
}

int	is_dir_parallel_to_obstacle_surface(\
		t_data *data, int axis, float t)
{
	return ((axis == 0 && fabsf(t) > \
				data->map->width * data->map->len_per_unit[axis]) \
 || (axis == 1 && fabsf(t) > \
				data->map->height * data->map->len_per_unit[axis]));
}

t_matrix	find_ray_end(\
			t_matrix *dir, const t_matrix *base, t_matrix *result, float t)
{
	result->mat[0][0] = base->mat[0][0] + t * dir->mat[0][0];
	result->mat[1][0] = base->mat[1][0] + t * dir->mat[1][0];
	result->mat[2][0] = base->mat[2][0] + t * dir->mat[2][0];
	return (*result);
}

int calc_column_dimensions(t_data *data, int step, t_point *p0, t_point *p1)
{
	t_matrix	dir;
	t_matrix	dir_cam_angle;
	t_matrix	current_slice;
	float		cam_angle_section;

	cam_angle_section = -1. * (data->camera.angle_camera / 2.f - (float) data->camera.angle_camera * (float) step / (float) data->camera.win_size.x_max);
	current_slice = euler2rot(0., 0., cam_angle_section);
	if (generate_direction_vector(&data->player.orientation, &dir) \
		|| multiply(&current_slice, &dir, &dir_cam_angle))
		return (1);
	float distance_to_wall = calc_distance_to_obstacle(data, &dir_cam_angle);
	distance_to_wall = distance_to_wall * cosf(fabsf(cam_angle_section) * DEG2RAD);
	if (step == data->camera.win_size.x_max / 2) {
		printf("distance screen: %f, distance object: %f\n", data->camera.distance_screen, distance_to_wall);
		printf("x: %f, y: %f, dir 0: %f, dir 1: %f, angle %f\n", data->player.pos.mat[0][0], data->player.pos.mat[1][0], dir.mat[0][0], dir.mat[1][0], cam_angle_section);
	}
	//*/
	p0->x = step;
	p1->x = step;
	p0->y = data->camera.win_size.y_max / 2.f + data->map->wall_height \
				/ 2. *  data->camera.distance_screen / distance_to_wall;
	p1->y = data->camera.win_size.y_max / 2.f - data->map->wall_height \
				/ 2. *  data->camera.distance_screen / distance_to_wall;
	p0->y = p0->y;
	p1->y = p1->y;
	if (p1->y < 0)
		p1->y = 0;
	if (p0->y < 0)
		p0->y = data->camera.win_size.y_max;
	(void) step;
	return (0);
}