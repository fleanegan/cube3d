#include "../inc/cube3d.h"

t_matrix	find_ray_end(\
		t_matrix *dir, const t_matrix *base, t_matrix *result, float t);
float		calc_distance_to_wall_matching_normal_vector(t_matrix *dir, \
		t_data *data, int normal_of_plane, int axis);
int			is_dir_parallel_to_obstacle_surface(\
		t_data *data, int axis, float t);

int
fill_rotation_entities(t_data *data, int step, t_matrix *dir_cam_angle,
					   float *cam_angle_section);

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

float calc_distance_to_obstacle(t_data *data, t_matrix *dir)
{
	int			normal_direction_plane;
	int			axis;
	float		result;
	float		tmp;

	axis = 0;
	result = FLT_MAX;
	while (axis < 2)
	{
		if (dir->mat[axis][0] > 0)
			normal_direction_plane = -1;
		else
			normal_direction_plane = 1;
		tmp = calc_distance_to_wall_matching_normal_vector(\
				dir, data, normal_direction_plane, axis);
		if (tmp < result && tmp > -0.001)
			result = tmp;
		axis++;
	}
	if (result > FLT_MAX * 0.99)
		return (-1);
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
		t = fabsf((float)(distance_wall - data->player.pos.mat[axis][0]) \
		/ ((float) fabs(dir->mat[axis][0] * (float) normal_of_plane)));
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

int calc_column_dimensions(t_data *data, int step, t_dimension_2d *wall_coordinates)
{
	t_matrix	dir_cam_angle;
	float		cam_angle_section;

	if (fill_rotation_entities(data, step, &dir_cam_angle, &cam_angle_section))
		return (1);
	float	distance_player_wall_shortest = calc_distance_to_obstacle(data, &dir_cam_angle) * cosf(fabsf(cam_angle_section) * DEG2RAD);
	float	tilt_angle = atanf((float) dir_cam_angle.mat[2][0] / sqrtf(powf((float) dir_cam_angle.mat[0][0], 2) + powf((float) dir_cam_angle.mat[1][0], 2))) * RAD2DEG;
	float	y_uppper_limit_view = (float) (distance_player_wall_shortest * tanf((tilt_angle + data->camera.angle_camera_vertical / 2.f) * DEG2RAD) + data->player.pos.mat[2][0]);
	float	head_room_until_wall = y_uppper_limit_view - data->map->wall_height;
	float	k = cosf(tilt_angle * DEG2RAD) * data->camera.distance_screen / distance_player_wall_shortest;
	float	head_room_transformed = (float) head_room_until_wall * k;
	float	foot_room = data->camera.win_size.y_max - head_room_until_wall  * k - data->map->wall_height * k;
	wall_coordinates->x_max = step;
	wall_coordinates->x_min = step;
	wall_coordinates->y_max = data->camera.win_size.y_max - head_room_transformed;
	wall_coordinates->y_min = foot_room;
	if (wall_coordinates->y_min < 0)
		wall_coordinates->y_min = 0;
	if (wall_coordinates->y_max >= data->camera.win_size.y_max)
		wall_coordinates->y_max = data->camera.win_size.y_max;
	if (step == data->camera.win_size.x_max / 2)
		printf("distance: %f\n", distance_player_wall_shortest);
	return (0);
}

int	fill_rotation_entities(\
	t_data *data, int step, t_matrix *dir_cam_angle, float *cam_angle_section)
{
	t_matrix	current_slice;
	t_matrix	dir;

	zero_init_point(&dir);
	zero_init_point(dir_cam_angle);
	zero_init_point(&current_slice);
	*cam_angle_section = -1.f * (data->camera.angle_camera_horizontal \
 / 2.f - (float) data->camera.angle_camera_horizontal * (float) step \
 / (float) data->camera.win_size.x_max);
	current_slice = euler2rot(0., 0., *cam_angle_section);
	if (generate_direction_vector(&data->player.orientation, &dir) \
			|| multiply(&current_slice, &dir, dir_cam_angle))
		return (1);
	return (0);
}
