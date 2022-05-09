/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:01:06 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 12:01:09 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

int	check_line_is_only_wall(t_map *map, int height)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		if (map->grid[x][height].mat[2][0] == 0)
			return (0);
		x++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	if (map == NULL)
		return (1);
	if (check_line_is_only_wall(map, 0) == 0 \
		|| check_line_is_only_wall(map, map->height - 1) == 0)
	{
		write(2, MAP_ERROR, ft_strlen(MAP_ERROR));
		return (1);
	}
	return (0);
}
