#include "../inc/cube3d.h"

static int	fill_map(t_map *map, int fd);
static int	is_spawn_point(char *content);

t_map	*parse_map(const char *string)
{
	int		fd;
	int		width;
	int		height;
	t_map	*result;

	fd = open(string, O_RDONLY);
	if (fd < 0 || measure_map(string, &width, &height))
		return (NULL);
	result = new_map(width, height);
	if (! result || fill_map(result, fd))
		free_map(&result);
	close(fd);
	result->tile_size = TILE_SIZE;
	return (result);
}

int	fill_map(t_map *map, int fd)
{
	char	*line;
	int		y_act;

	y_act = 0;
	while (gnl(fd, &line))
	{
		if (parse_line(line, map, y_act))
		{
			free(line);
			return (1);
		}
		free(line);
		y_act++;
	}
	gnl(fd, NULL);
	return (0);
}

int	parse_line(char *line, t_map *map, int y_act)
{
	char		**split_line;
	int			x_act;
	t_matrix	*point_tmp;

	x_act = 0;
	split_line = ft_split(line, ' ');
	if (! split_line)
		return (1);
	while (split_line[x_act])
	{
		point_tmp = &map->grid[x_act][y_act];
		zero_init_point(point_tmp);
		point_tmp->mat[0][0] = x_act;
		point_tmp->mat[1][0] = y_act;
		if (is_spawn_point(split_line[x_act]))
		{
			map->spawn_point = point_tmp;
			map->spawn_orientation = split_line[x_act][0];
		}
		point_tmp->mat[2][0] = ft_atoi(split_line[x_act]);
		x_act++;
	}
	free_2d_array((void **) split_line);
	return (0);
}

int	is_spawn_point(char *content)
{
	return (ft_strcmp(content, "E") == 0 \
			|| ft_strcmp(content, "S") == 0 \
			|| ft_strcmp(content, "W") == 0 \
			|| ft_strcmp(content, "N") == 0);
}
