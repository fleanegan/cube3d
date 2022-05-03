/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:33 by                   #+#    #+#             */
/*   Updated: 2022/05/03 18:19:24 by tsiguenz         ###   ########.fr       */
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

t_map	*init_map(void)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (result == NULL)
		return (NULL);
	ft_bzero(result, sizeof(t_map));
	result->ceilling_color = COLOR_UNINITIALISED;
	result->floor_color = COLOR_UNINITIALISED;
	result->tile_size = TILE_SIZE;
	return (result);
}

void	*free_map(t_map **map)
{
	free((*map)->texture[TEXTURE_NO]);
	free((*map)->texture[TEXTURE_SO]);
	free((*map)->texture[TEXTURE_WE]);
	free((*map)->texture[TEXTURE_EA]);
	if ((*map)->grid != NULL)
		free_2d_array((void **)(*map)->grid);
	free(*map);
	*map = NULL;
	return (NULL);
}
