#include "../inc/cube3d.h"

void remove_wall(t_data *data);

#ifndef TESTING

int	handle_key_press(int keycode, t_data *data)
{
	printf("pressed: %d\n", keycode);
	if (keycode == KEY_ESC)
		tear_down_mlx_session(data);
	if (keycode == KEY_DOWN)
		data->player.movements.backward = 1;
	if (keycode == KEY_UP)
		data->player.movements.forward = 1;
	if (keycode == KEY_RIGHT)
		data->player.movements.right = 1;
	if (keycode == KEY_LEFT)
		data->player.movements.left = 1;
	if (keycode == KEY_ARROW_UP)
		data->player.movements.rot_up = 1;
	if (keycode == KEY_ARROW_DOWN)
		data->player.movements.rot_down = 1;
	if (keycode == KEY_ARROW_LEFT)
		data->player.movements.rot_left = 1;
	if (keycode == KEY_ARROW_RIGHT)
		data->player.movements.rot_right = 1;
	if (keycode == 47)
		data->player.admin_mode++;
	if (keycode == 32)
		remove_wall(data);
	return (0);
}

void remove_wall(t_data *data)
{
	t_matrix	dir;
	t_ray		ray;

	generate_direction_vector(&data->player.orientation, &dir);
	ray = calc_distance_to_obstacle(data, &dir);
	if(ray.object_at_contact != NULL)
		ray.object_at_contact->mat[2][0] = 0.0;
}

int	handle_key_release(int keycode, t_data *data)
{
	printf("released: %d\n", keycode);
	if (keycode == KEY_ESC)
		tear_down_mlx_session(data);
	if (keycode == KEY_DOWN)
		data->player.movements.backward = 0;
	if (keycode == KEY_UP)
		data->player.movements.forward = 0;
	if (keycode == KEY_RIGHT)
		data->player.movements.right = 0;
	if (keycode == KEY_LEFT)
		data->player.movements.left = 0;
	if (keycode == KEY_ARROW_UP)
		data->player.movements.rot_up = 0;
	if (keycode == KEY_ARROW_DOWN)
		data->player.movements.rot_down = 0;
	if (keycode == KEY_ARROW_LEFT)
		data->player.movements.rot_left = 0;
	if (keycode == KEY_ARROW_RIGHT)
		data->player.movements.rot_right = 0;
	return (0);
}

int	red_cross_handler(t_data *data)
{
	tear_down_mlx_session(data);
	return (0);
}
#endif
