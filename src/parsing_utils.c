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

int	is_spawn_point(char c)
{
	return (c == 'E' || c == 'W' || c == 'N' || c == 'S');
}

int	len_split_map(char *line)
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
	//printf("line = %s res = %d\n", line, res);
	return (res);
}

char	*clean_line(char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(len_split_map(line) + 1 * sizeof(char *));
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
