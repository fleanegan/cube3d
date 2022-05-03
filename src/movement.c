#include "../inc/cube3d.h"

void	move(t_data *data)
{
	t_matrix	tmp;
	t_matrix	direction;

	zero_init_point(&direction);
	zero_init_point(&tmp);
	if (data->player.movements.left)
		direction.mat[1][0] = -10;
	if (data->player.movements.right)
		direction.mat[1][0] = 10;
	if (data->player.movements.backward)
		direction.mat[0][0] = -10;
	if (data->player.movements.forward)
		direction.mat[0][0] = 10;
	multiply(&data->player.orientation, &direction, &tmp);
	data->player.pos.mat[0][0] += tmp.mat[0][0];
	data->player.pos.mat[1][0] += tmp.mat[1][0];
}

// multiplication is inverse for rotations around z to rotate around the global axis
void	rotate(t_data *data)
{
	t_matrix	rot_left;
	t_matrix	rot_down;
	t_matrix	rot_up;
	t_matrix	rot_right;
	t_matrix	tmp;

	zero_init_rotation_matrix(&tmp);
	tmp = euler2rot(0, 0, 0);
	rot_left = euler2rot(0, 0, -5.);
	rot_right = euler2rot(0, 0, 5.);
	rot_up = euler2rot(0, 5, 0);
	rot_down = euler2rot(0, -5, 0);
	if (data->player.movements.rot_down)
		multiply(&data->player.orientation, &rot_down , &tmp);
	if (data->player.movements.rot_up)
		multiply(&data->player.orientation, &rot_up, &tmp);
	if (data->player.movements.rot_left)
		multiply(&rot_left, &data->player.orientation, &tmp);
	if (data->player.movements.rot_right)
		multiply(&rot_right, &data->player.orientation, &tmp);
	if (data->player.movements.rot_right != 0 \
		|| data->player.movements.rot_left != 0 \
		|| data->player.movements.rot_up != 0 \
		|| data->player.movements.rot_down != 0)
		data->player.orientation = tmp;
}
