/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:02:36 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:02:37 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

#ifndef TESTING

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		tear_down_mlx_session(data, 0);
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
		remove_interior_walls(data);
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		tear_down_mlx_session(data, 0);
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
	tear_down_mlx_session(data, 0);
	return (0);
}
#endif
