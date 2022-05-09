/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:02:56 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:02:59 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

t_matrix	**new_grid(t_map *map)
{
	t_matrix	**result;
	int			width;

	width = map->width;
	result = malloc((width + 1) * sizeof (t_matrix *));
	if (! result)
		return (error_parsing(NULL, MALLOC_FAIL));
	result[map->width] = NULL;
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
	init_points_to_wall(map, result);
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
	result->c_color = COLOR_UNINITIALISED;
	result->f_color = COLOR_UNINITIALISED;
	result->grid = new_grid(result);
	if (! result->grid)
		return (NULL);
	return (result);
}

void	*free_map(t_map **map)
{
	if (*map == NULL)
		return (NULL);
	free((*map)->texture_name[TEXTURE_NO]);
	free((*map)->texture_name[TEXTURE_SO]);
	free((*map)->texture_name[TEXTURE_WE]);
	free((*map)->texture_name[TEXTURE_EA]);
	if ((*map)->grid != NULL)
		free_2d_array((void **)(*map)->grid);
	free(*map);
	*map = NULL;
	return (NULL);
}

#ifndef TESTING

void	free_textures(t_data *data)
{
	if (data->map->mouse_texture)
		mlx_destroy_image(data->mlx.mlx, data->map->mouse_texture);
	if (data->map->texture[0])
		mlx_destroy_image(data->mlx.mlx, data->map->texture[0]);
	if (data->map->texture[1])
		mlx_destroy_image(data->mlx.mlx, data->map->texture[1]);
	if (data->map->texture[2])
		mlx_destroy_image(data->mlx.mlx, data->map->texture[2]);
	if (data->map->texture[3])
		mlx_destroy_image(data->mlx.mlx, data->map->texture[3]);
}

#endif
