/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:21:45 by                   #+#    #+#             */
/*   Updated: 2022/02/01 18:21:45 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

#ifndef TESTING

void	handle_linear_key_events(int keycode, t_data *img)
{
	if (keycode == 45)
		img->z_scale += 0.1f;
	else if (keycode == 61)
		img->z_scale -= 0.1f;
	else if (keycode == 65362)
		img->y_offset += 0.1f;
	else if (keycode == 65364)
		img->y_offset -= 0.1f;
	else if (keycode == 65361)
		img->x_offset += 0.1f;
	else if (keycode == 65363)
		img->x_offset -= 0.1f;
	else if (keycode == 46)
		img->zoom += 0.1f;
	else if (keycode == 44)
		img->zoom -= 0.1f;
}

int	key_handler(int keycode, t_data *img)
{
	if (keycode == 65307 || keycode == 38)
		tear_down_mlx_session(img);
	handle_linear_key_events(keycode, img);
	render_frame(img);
	return (0);
}

#endif