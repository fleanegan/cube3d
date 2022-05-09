/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:11 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 12:14:03 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

int	parse_texture(char **dest, char *line)
{
	int		i;
	int		y;

	i = 0;
	if (*dest != NULL)
		return (1);
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	if (i == 0)
		return (print_error(TEXTURE_ERROR));
	y = i;
	while (line[y] && ft_isspace(line[y]) == 0)
		y++;
	if (y > i)
		line[y] = '\0';
	if (line[y + 1] != '\0')
		return (print_error(TEXTURE_ERROR));
	*dest = ft_strdup(line + i);
	if (*dest == NULL)
		return (print_error(MALLOC_FAIL));
	return (0);
}

char	*go_next_field(char *line)
{
	char	*tmp;

	tmp = ft_strchr(line, ',');
	if (tmp == NULL)
	{
		print_error(COLOR_FAIL);
		return (NULL);
	}
	tmp++;
	return (tmp);
}

int	set_color(int *color, char *line)
{
	if (line == NULL)
		return (1);
	*color = ft_atoi(line);
	if (*color < 0 || *color > 255)
		return (print_error(COLOR_OUT_OF_RANGE));
	return (0);
}

int	parse_color(int *dest, char *line)
{
	int		r;
	int		g;
	int		b;

	if (*dest != COLOR_UNINITIALISED)
		return (print_error(COLOR_DUPLICATE));
	if (set_color(&r, line))
		return (1);
	line = go_next_field(line);
	if (set_color(&g, line))
		return (1);
	line = go_next_field(line);
	if (set_color(&b, line))
		return (1);
	while (*line && ft_isspace(*line) == 1)
		line++;
	while (*line && ft_isdigit(*line) == 1)
		line++;
	if (*line != '\n')
		return (print_error(COLOR_FAIL));
	*dest = r << 16 | g << 8 | b;
	return (0);
}

void	parse_infos(t_map **result, char *line)
{
	if ((ft_strncmp(line, "NO", 2) == 0 && parse_texture(\
	&(*result)->texture_name[TEXTURE_NO], line + 2) == 0) \
 || (ft_strncmp(line, "SO", 2) == 0 && parse_texture(\
		&(*result)->texture_name[TEXTURE_SO], line + 2) == 0) \
 || (ft_strncmp(line, "WE", 2) == 0 && parse_texture(\
		&(*result)->texture_name[TEXTURE_WE], line + 2) == 0) \
 || (ft_strncmp(line, "EA", 2) == 0 && parse_texture(\
		&(*result)->texture_name[TEXTURE_EA], line + 2) == 0) \
 || (ft_strncmp(line, "F", 1) == 0 \
			&& parse_color(&(*result)->f_color, line + 1) == 0) \
 || (ft_strncmp(line, "C", 1) == 0 \
			&& parse_color(&(*result)->c_color, line + 1) == 0))
		return ;
	if (line_is_only_space(line) == 0)
	{
		print_error(MAP_ERROR);
		free_map(result);
	}
}
