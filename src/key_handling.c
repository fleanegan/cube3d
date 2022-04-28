#include "../inc/cube3d.h"

#ifndef TESTING

void	move(t_data *data, t_matrix *direction)
{
	t_matrix	tmp;

	zero_init_point(&tmp);
	multiply(&data->player.orientation, direction, &tmp);
	data->player.pos.mat[0][0] += tmp.mat[0][0];
	data->player.pos.mat[1][0] += tmp.mat[1][0];
	data->player.pos.mat[2][0] += tmp.mat[2][0];
	print_matrix(&tmp);
}

void	handle_linear_key_events(int keycode, t_data *data)
{
	t_matrix	rot_left;
	t_matrix	rot_right;
	t_matrix	move_forward;
	t_matrix	move_backward;
	t_matrix	move_left;
	t_matrix	move_right;
	t_matrix	tmp;

	rot_left = euler2rot(0, 0, -5.);
	rot_right = euler2rot(0, 0, 5.);
	zero_init_point(&move_forward);
	zero_init_point(&tmp);
	zero_init_point(&move_backward);
	zero_init_point(&move_left);
	zero_init_point(&move_right);
	move_backward.mat[0][0] = 10;
	move_forward.mat[0][0] = -10;
	move_left.mat[1][0] = 10;
	move_right.mat[1][0] = -10;
	//TODO: inversed ?
	if (keycode == KEY_DOWN)
		move(data, &move_backward);
	else if (keycode == KEY_UP)
		move(data, &move_forward);
	else if (keycode == KEY_RIGHT)
		move(data, &move_right);
	else if (keycode == KEY_LEFT)
		move(data, &move_left);
	else if (keycode == KEY_ARROW_LEFT)
	{
		multiply(&data->player.orientation, &rot_left, &tmp);
		data->player.orientation = tmp;
	}
	else if (keycode == KEY_ARROW_RIGHT)
	{
		multiply(&data->player.orientation, &rot_right, &tmp);
		data->player.orientation = tmp;
	}
}

int	key_handler(int keycode, t_data *data)
{
	printf("keycode: %d\n", keycode);
	if (keycode == KEY_ESC || keycode == 38) //TODO: what is 38 (define) ?
		tear_down_mlx_session(data);
	else
		handle_linear_key_events(keycode, data);
	render_frame(data);
	return (0);
}

int	red_cross_handler(t_data *data)
{
	tear_down_mlx_session(data);
	return (0);
}
#endif
