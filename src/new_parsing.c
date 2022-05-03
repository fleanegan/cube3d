#include "../inc/cube3d.h"

void	*error_parsing(char *str)
{
	ft_putstr_fd(str, 2);
	return (NULL);
}

int	header_infos_are_set(t_map *result)
{
	if (result->texture[TEXTURE_NO] == NULL ||
		result->texture[TEXTURE_SO] == NULL ||
		result->texture[TEXTURE_WE] == NULL ||
		result->texture[TEXTURE_EA] == NULL ||
		result->ceilling_color == COLOR_UNINITIALISED ||
		result->floor_color == COLOR_UNINITIALISED)
		return (0);
	return (1);
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
	result = init_map();
	if (result == NULL)
		return (error_parsing(MALLOC_FAIL));
	while (gnl(fd, &line))
	{
		if (header_infos_are_set(result) == 0)
			parse_infos(result, line);
		free(line);
	}
	return (result);
}
