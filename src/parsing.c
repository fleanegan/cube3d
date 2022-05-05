#include "../inc/cube3d.h"

int	parse_line(char *line, t_map *map, int y_act)
{
	char		*line_clean;
	int			i;
	t_matrix	*point_tmp;

	i = 0;
	line_clean = clean_line(line);
	if (! line_clean)
		return (1);
	while (line_clean[i])
	{
		point_tmp = &map->grid[i][y_act];
		zero_init_point(point_tmp);
		point_tmp->mat[0][0] = i;
		point_tmp->mat[1][0] = y_act;
		if (is_spawn_point(line_clean[i]))
		{
			map->spawn_point = point_tmp;
			map->spawn_orientation = line_clean[i];
		}
		point_tmp->mat[2][0] = line_clean[i] - 48;
		i++;
	}
	free(line_clean);
	return (0);
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
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (error_parsing(&result, OPENING_FILE));
	result = init_map(file_name);
	if (result == NULL)
	{
		close(fd);
		return (error_parsing(&result, MALLOC_FAIL));
	}
	while (gnl(fd, &line) != 0 && result != NULL)
	{
		if (header_infos_are_set(result) == 0)
			parse_infos(&result, line);
		else
		{
			parse_line(line, result, y_act);//protect error
			if (is_line_of_map(line) == 1)
				y_act++;
		}
		free(line);
	}
	close(fd);
	if (!result || header_infos_are_set(result) == 0)
		free_map(&result);
	return (result);
}
