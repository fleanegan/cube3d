/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:33 by                   #+#    #+#             */
/*   Updated: 2022/05/06 10:58:46 by tsiguenz         ###   ########.fr       */
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
		return (error_parsing(NULL, MALLOC_FAIL));
	result[width] = NULL;
	while (width--)
	{
		result[width] = malloc((map->height) * sizeof(t_matrix));
		if (! result[width])
		{
			free_2d_array((void **) result);
			return (error_parsing(NULL, MALLOC_FAIL));
		}
		ft_bzero(result[width], map->height * sizeof(t_matrix *));
	}
	return (result);
}

t_map	*init_map(const char *file_name)
{
	t_map	*result;
	int		width;
	int		height;

	width = 0;
	height = 0;
	result = malloc(sizeof(t_map));
	if (result == NULL)
		return (error_parsing(NULL, MALLOC_FAIL));
	ft_bzero(result, sizeof(t_map));
	if (measure_map(file_name, &width, &height) == 1)
		return (free_map(&result));
	result->width = width;
	result->wall_height = TILE_SIZE;
	result->height = height;
	result->ceilling_color = COLOR_UNINITIALISED;
	result->floor_color = COLOR_UNINITIALISED;
	result->grid = new_grid(result);
	if (! result->grid)
		return (NULL);
	return (result);
}

void	*free_map(t_map **map)
{
	if (*map == NULL)
		return (NULL);
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
