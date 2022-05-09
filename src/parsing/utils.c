/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:37 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 12:00:39 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

void	*error_parsing(t_map **result, char *str)
{
	ft_putstr_fd(str, 2);
	free_map(result);
	return (NULL);
}

int	header_infos_are_set(t_map *result)
{
	if (result->texture_name[TEXTURE_NO] == NULL \
	|| result->texture_name[TEXTURE_SO] == NULL \
	|| result->texture_name[TEXTURE_WE] == NULL \
	|| result->texture_name[TEXTURE_EA] == NULL \
	|| result->c_color == COLOR_UNINITIALISED \
	|| result->f_color == COLOR_UNINITIALISED)
		return (0);
	return (1);
}

int	is_spawn_point(char c)
{
	return (c == 'E' || c == 'W' || c == 'N' || c == 'S');
}

int	line_is_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0');
}

int	is_cub_file(const char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
	{
		if (i > 0 \
				&& file_name[i] == '.' \
				&& ft_strncmp(file_name + i, ".cub", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}
