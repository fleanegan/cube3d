#include "../inc/cube3d.h"

int is_colision(t_data *data, t_matrix *waling_dir);

void	move(t_data *data)
{
	t_matrix	tmp;
	t_matrix	waling_dir;


	zero_init_point(&waling_dir);
	zero_init_point(&tmp);
	if (data->player.movements.left)
		waling_dir.mat[1][0] = -10;
	if (data->player.movements.right)
		waling_dir.mat[1][0] = 10;
	if (data->player.movements.backward)
		waling_dir.mat[0][0] = -10;
	if (data->player.movements.forward)
		waling_dir.mat[0][0] = 10;
	multiply(&data->player.orientation, &waling_dir, &waling_dir);
	if (is_colision(data, &waling_dir))
		return ;
	data->player.pos.mat[0][0] += waling_dir.mat[0][0];
	data->player.pos.mat[1][0] += waling_dir.mat[1][0];
}

int is_colision(t_data *data, t_matrix *waling_dir)
{
	t_ray		ray;
	float		stride;
	stride = sqrtf(powf(waling_dir->mat[0][0], 2) + powf(waling_dir->mat[1][0], 2));
	ray = calc_distance_to_obstacle(data, waling_dir);
	if (ray.distance < 10.f || ray.distance < stride)
		return (1);
	return (0);
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
