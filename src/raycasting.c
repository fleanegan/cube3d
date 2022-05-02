#include "../inc/cube3d.h"



int	raycast_one_slice(t_data *data, int step, t_dimension_2d *wall_coordinates)
{
	t_matrix	dir_cam_angle;
	float		cam_angle;
	float		distance_wall;

	if (prepare_slice_orientation(data, step, &dir_cam_angle, &cam_angle))
		return (1);
	distance_wall = calc_distance_to_obstacle(data, &dir_cam_angle) \
 		* cosf(fabsf(cam_angle) * DEG2RAD);
	*wall_coordinates = calc_wall_dimensions_slice(\
		data, step, &dir_cam_angle, distance_wall);
	clip_to_screen_limits(data, wall_coordinates);
	if (step == data->camera.win_size.x_max / 2)
		printf("distance: %f\n", distance_wall);
	return (0);
}

t_dimension_2d	calc_wall_dimensions_slice(t_data *data, int step, \
				t_matrix *dir_cam_angle, float distance_wall)
{
	float			tilt_angle;
	float			y_upper_limit_view;
	float 			gap_above_wall;
	float			k;
	t_dimension_2d	result;

	tilt_angle = atanf((float) (*dir_cam_angle).mat[2][0] /
		sqrtf(powf((float) (*dir_cam_angle).mat[0][0], 2) +
		powf((float) (*dir_cam_angle).mat[1][0], 2))) * RAD2DEG;
	y_upper_limit_view = (float) (distance_wall * \
		tanf((tilt_angle + data->camera.angle_camera_vertical / 2.f) \
		* DEG2RAD) + data->player.pos.mat[2][0]);
	gap_above_wall = y_upper_limit_view - data->map->wall_height;
	k = cosf(tilt_angle * DEG2RAD) * data->camera.distance_screen / distance_wall;
	result.x_max = step;
	result.x_min = step;
	result.y_max = data->camera.win_size.y_max - (float) gap_above_wall * k;
	result.y_min = result.y_max - data->map->wall_height * k;
	return (result);
}

int	prepare_slice_orientation(\
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

void	clip_to_screen_limits(t_data *data, t_dimension_2d *wall_coordinates)
{
	if (wall_coordinates->y_min < 0)
		wall_coordinates->y_min = 0;
	if (wall_coordinates->y_max >= data->camera.win_size.y_max)
		wall_coordinates->y_max = data->camera.win_size.y_max;
}
