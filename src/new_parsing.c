#include "../inc/cube3d.h"

void	*error_parsing(char *str)
{
	ft_putstr_fd(str, 2);
	return (NULL);
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

char	*parse_texture(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) == 1)
		i++;
	if (i == 0)
		return (error_parsing(TEXTURE_ERROR));
	return (line + i);
}

int	parse_color(char *line)
{
	int	res;

	res = ft_atoi(line);
	return (res);
}

t_map	*parse_infos(t_map *result, char *line)
{

	if (ft_strncmp(line, "NO", 2) == 0)
		result->north_texture = ft_strdup(parse_texture(line + 2));
	if (ft_strncmp(line, "SO", 2) == 0)
		result->south_texture = ft_strdup(parse_texture(line + 2));
	if (ft_strncmp(line, "WE", 2) == 0)
		result->west_texture = ft_strdup(parse_texture(line + 2));
	if (ft_strncmp(line, "EA", 2) == 0)
		result->east_texture = ft_strdup(parse_texture(line + 2));
	if (ft_strncmp(line, "F", 1) == 0)
		result->floor_color = parse_color(line + 1);
	if (ft_strncmp(line, "C", 1) == 0)
		result->ceilling_color = parse_color(line + 1);
	return (result);
}

t_map	*parse(const char *file_name)
{
	int		fd;
	char	*line;
	t_map	*result;

	if (is_cub_file(file_name) == 0)
		return (error_parsing(BAD_FILE_NAME));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (error_parsing(OPENING_FILE));
	result = malloc(sizeof(t_map));
	if (result == NULL)
		return (error_parsing(MALLOC_FAIL));
	while (gnl(fd, &line))
	{
		parse_infos(result, line);
		free(line);
	}
	return (result);
}
