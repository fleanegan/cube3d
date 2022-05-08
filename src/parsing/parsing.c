#include "../../inc/cube3d.h"

static t_map	*parse_line(char *line, t_map **result, int *y_act);
static t_matrix	*set_up_point(t_map *const *map, int y_act, \
				int i, t_matrix *point_tmp);

int	parse_map_line(char *line, t_map **map, int y_act)
{
	char		*line_clean;
	int			i;
	t_matrix	*point_tmp;

	i = 0;
	line_clean = clean_line(line);
	if (!line_clean)
		return (free_map(map) == NULL);
	while (line_clean[i])
	{
		point_tmp = set_up_point(map, y_act, i, point_tmp);
		point_tmp->mat[2][0] = line_clean[i] - '0';
		if (is_spawn_point(line_clean[i]))
		{
			if ((*map)->spawn_point != 0)
			{
				free(line_clean);
				return (write(2, ERROR_MULTIPLE_SPAWNPOINT, \
				ft_strlen(ERROR_MULTIPLE_SPAWNPOINT)));
			}
			(*map)->spawn_point = point_tmp;
			point_tmp->mat[2][0] = 0;
			(*map)->spawn_orientation = line_clean[i];
		}
		i++;
	}
	free(line_clean);
	return (0);
}

t_matrix	*set_up_point(t_map *const *map, int y_act, \
			int i, t_matrix *point_tmp)
{
	point_tmp = &(*map)->grid[i][y_act];
	zero_init_point(point_tmp);
	point_tmp->mat[0][0] = i;
	point_tmp->mat[1][0] = y_act;
	return (point_tmp);
}

int	spawn_is_set(t_map *result)
{
	if (result == NULL)
		return (0);
	if (result->spawn_orientation == 0)
	{
		ft_putendl_fd("Error\nNo spawn point in map", 2);
		return (0);
	}
	return (1);
}

t_map	*parse(const char *file_name)
{
	int		fd;
	char	*line;
	t_map	*result;
	int		y_act;

	result = NULL;
	y_act = 0;
	if (is_cub_file(file_name) == 0)
		return (error_parsing(&result, BAD_FILE_NAME));
	result = init_map(file_name);
	if (result == NULL)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (error_parsing(&result, OPENING_FILE));
	while (result != NULL && gnl(fd, &line) != 0)
	{
		result = parse_line(line, &result, &y_act);
		free(line);
	}
	close(fd);
	if ((result && header_infos_are_set(result) == 0) || !spawn_is_set(result) \
		|| check_map(result) == 1)
		free_map(&result);
	return (result);
}

t_map	*parse_line(char *line, t_map **result, int *y_act)
{
	if (header_infos_are_set((*result)) == 0)
		parse_infos(result, line);
	else
	{
		if (parse_map_line(line, result, *y_act))
			return (error_parsing(result, NULL));
		if (line && is_line_of_map(line) == 1)
			(*y_act)++;
	}
	return (*result);
}
