/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:00:07 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 12:14:21 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

static int	initialize(const char *file_name, int *width, int *height, int *fd);
int			calc_width(char *line);
int			prepare_exit(int fd, char **line, int status);

int	is_line_of_map(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) == 1)
		i++;
	if (line[i] != '1')
		return (0);
	while (line[i] == '0' || line[i] == '1' || ft_isspace(line[i]) \
			|| is_spawn_point(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	while (ft_isdigit(line[i]) == 0)
		i--;
	if (line[i] != '1')
		return (0);
	return (1);
}

int	set_dimensions(char *line, int *height, int *width)
{
	char	*line_clean;
	int		tmp_height;

	tmp_height = 0;
	line_clean = clean_line(line);
	if (line_clean == NULL)
		return (1);
	tmp_height = ft_strlen(line_clean);
	free(line_clean);
	if (tmp_height > *height)
		*height = tmp_height;
	(*width)++;
	return (0);
}

int	measure_map(const char *file_name, int *height, int *width)
{
	int		fd;
	char	*line;
	int		in_map;

	in_map = 0;
	if (initialize(file_name, height, width, &fd))
		return (1);
	while (gnl(fd, &line))
	{
		if (is_line_of_map(line) == 1)
		{
			in_map = 1;
			if (set_dimensions(line, height, width) == 1)
				return (prepare_exit(fd, &line, 1));
		}
		if (is_line_of_map(line) == 0 && in_map == 1)
		{
			write(2, MAP_ERROR, ft_strlen(MAP_ERROR));
			return (prepare_exit(fd, &line, 1));
		}
		free(line);
	}
	close(fd);
	return (in_map == 0 && write(2, MAP_ERROR, ft_strlen(MAP_ERROR)));
}

static int	initialize(const char *file_name, int *width, int *height, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (write(2, OPENING_FILE, ft_strlen(OPENING_FILE)));
	*height = 0;
	*width = 0;
	return (0);
}

int	prepare_exit(int fd, char **line, int status)
{
	gnl(-1, NULL);
	free(*line);
	*line = NULL;
	close(fd);
	return (status);
}
