#include "../inc/cube3d.h"

int	raycast_one_slice(t_data *data, int step, t_dimension_2d *wall_coordinates)
{
	t_matrix	slice_dir;
	float		cam_angle;
	float		distance_wall;

	if (prepare_slice_orientation(data, step, &slice_dir, &cam_angle))
		return (1);
	distance_wall = calc_distance_to_obstacle(data, &slice_dir) \
		* cosf(fabsf(cam_angle) * DEG2RAD);
		* wall_coordinates = calc_wall_dimensions_slice(\
			data, step, &slice_dir, distance_wall);
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
	t_data *data, int step, t_matrix *slice_dir, float *cam_angle)
{
	t_matrix	angle_as_rot;
	t_matrix	orientation_slice;

	zero_init_point(slice_dir);
	*cam_angle = -1.f * (data->camera.angle_camera_horizontal \
 		/ 2.f - (float) data->camera.angle_camera_horizontal * (float) step \
		/ (float) data->camera.win_size.x_max);
	angle_as_rot = euler2rot(0., 0., *cam_angle);
	multiply(&angle_as_rot, &data->player.orientation, &orientation_slice);
	if (generate_direction_vector(&orientation_slice, slice_dir))
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
