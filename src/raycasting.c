#include "../inc/cube3d.h"

int	raycast_one_slice(t_data *data, int step, t_ray *ray)
{
	t_matrix	slice_dir;
	float		cam_angle;

	if (prepare_slice_orientation(data, step, &slice_dir, &cam_angle))
		return (1);
	*ray = calc_distance_to_obstacle(data, &slice_dir);
	ray->distance = ray->distance \
		* cosf(fabsf(cam_angle) * DEG2RAD);
	calc_wall_dimensions_slice(data, step, &slice_dir, ray);
	clip_to_screen_limits(data, ray);
	return (0);
}

void	calc_wall_dimensions_slice(\
		t_data *data, int step, t_matrix *dir_cam_angle, t_ray *ray)
{
	float			tilt_angle;
	float			y_upper_limit_view;
	float 			gap_above_wall;
	float			k;
	float			wall_height;

	tilt_angle = atanf((float) (*dir_cam_angle).mat[2][0] /
		sqrtf(powf((float) (*dir_cam_angle).mat[0][0], 2) +
		powf((float) (*dir_cam_angle).mat[1][0], 2))) * RAD2DEG;
	y_upper_limit_view = (float) (ray->distance * \
		tanf((tilt_angle + data->camera.angle_camera_vertical / 2.f) \
		* DEG2RAD) + data->player.pos.mat[2][0]);
	wall_height = data->map->wall_height;
	if (ray->object_at_contact != NULL)
		wall_height = data->map->wall_height * (ray->object_at_contact->mat[2][0]);
	gap_above_wall = y_upper_limit_view - wall_height;
	k = cosf(tilt_angle * DEG2RAD) * data->camera.distance_screen / ray->distance;
	ray->x_clipped_screen_coordinates = step;
	ray->y_min_screen_coordinates = (float) gap_above_wall * k;
	ray->y_max_screen_coordinates = ray->y_min_screen_coordinates + wall_height * k;
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

void	clip_to_screen_limits(t_data *data, t_ray *ray)
{
	ray->y_min_clipped_screen_coordinates = ray->y_min_screen_coordinates;
	ray->y_max_clipped_screen_coordinates = ray->y_max_screen_coordinates;
	if (ray->y_min_clipped_screen_coordinates < 0)
		ray->y_min_clipped_screen_coordinates = 0;
	if (ray->y_max_clipped_screen_coordinates >= data->camera.win_size.y_max)
		ray->y_max_clipped_screen_coordinates = data->camera.win_size.y_max;
}
