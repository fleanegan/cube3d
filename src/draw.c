/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:38 by                   #+#    #+#             */
/*   Updated: 2022/02/01 15:00:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	draw_1px_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	turn_all_pixels_black(t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < img->win_size.x_max)
	{
		y = 0;
		while (y < img->win_size.y_max)
		{
			draw_1px_to_img(img, x, y, 0);
			y++;
		}
		x++;
	}
}
