/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:33 by                   #+#    #+#             */
/*   Updated: 2022/02/01 14:44:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/cube3d.h"

void	set_point(t_point *pt, double x, double y, double z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

t_matrix	**new_grid(t_map *map)
{
	t_matrix	**result;
	int			width;

	width = map->width;
	result = malloc((width + 1) * sizeof (t_matrix *));
	if (! result)
		return (NULL);
	result[width] = NULL;
	while (width--)
	{
		result[width] = malloc((map->height) * sizeof(t_matrix));
		if (! result[width])
		{
			free_2d_array((void **) result);
			return (NULL);
		}
	}
	return (result);
}

t_map	*new_map(int width, int height)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (! result)
		return (NULL);
	result->width = width;
	result->height = height;
	result->grid = new_grid(result);
	if (! result->grid)
		return (free_map(&result));
	return (result);
}

void	*free_map(t_map **map)
{
	free_2d_array((void **)(*map)->grid);
	free(*map);
	*map = NULL;
	return (NULL);
}
