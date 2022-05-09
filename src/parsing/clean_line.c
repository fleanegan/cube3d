/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:03:47 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:03:49 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

int	len_split_map_line(char *line)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || is_spawn_point(line[i]) == 1)
			res++;
		i++;
	}
	return (res);
}

char	*clean_line(char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(len_split_map_line(line) + 1 * sizeof(char *));
	if (res == NULL)
		return (error_parsing(NULL, MALLOC_FAIL));
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || is_spawn_point(line[i]) == 1)
		{
			res[j] = line[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
