#include "../inc/cube3d.h"

void	*error_parsing(t_map **result, char *str)
{
	ft_putstr_fd(str, 2);
	free_map(result);
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

	result = NULL;
	if (is_cub_file(file_name) == 0)
		return (error_parsing(&result, BAD_FILE_NAME));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (error_parsing(&result, OPENING_FILE));
	result = init_map();
	if (result == NULL)
	{
		close(fd);
		return (error_parsing(&result, MALLOC_FAIL));
	}
	while (gnl(fd, &line) && result != NULL)
	{
		if (header_infos_are_set(result) == 0)
			parse_infos(&result, line);
		free(line);
		if (result == NULL)
		{
			close(fd);
			gnl(-1, 0);
			return (NULL);
		}
	}
	close(fd);
	if (header_infos_are_set(result) == 0)
		free_map(&result);
	return (result);
}
