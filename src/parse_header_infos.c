#include "../inc/cube3d.h"

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

int	parse_texture(char **dest, char *line)
{
	int		i;
	int		y;

	i = 0;
	if (*dest != NULL)
		return (write(2, TEXTURE_DUPLICATE, ft_strlen(TEXTURE_DUPLICATE)));
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	if (i == 0)
		return (write(2, TEXTURE_ERROR, ft_strlen(TEXTURE_ERROR)));
	y = i;
	while (line[y] && ft_isspace(line[y]) == 0)
		y++;
	if (y > i)
		line[y] = '\0';
	*dest = ft_strdup(line + i);
	if (*dest == NULL)
		return (write(2, MALLOC_FAIL, ft_strlen(MALLOC_FAIL)));
	return (0);
}

// TODO: protect -1 if error
int	parse_color(char *line)
{
	char	*tmp;
	int		r;
	int		g;
	int		b;

	r = ft_atoi(line);
	if (r < 0 || r > 255)
		return (COLOR_OUT_OF_RANGE);
	tmp = ft_strchr(line, ',');
	tmp++;
	g = ft_atoi(tmp);
	if (g < 0 || g > 255)
		return (COLOR_OUT_OF_RANGE);
	tmp = ft_strchr(tmp, ',');
	tmp++;
	b = ft_atoi(tmp);
	if (b < 0 || b > 255)
		return (COLOR_OUT_OF_RANGE);
	return (r << 16 | g << 8 | b);
}

t_map	*parse_infos(t_map *result, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 \
		&& parse_texture(&result->texture[TEXTURE_NO], line + 2) != 0)
		free_map(&result);
	if (ft_strncmp(line, "SO", 2) == 0 \
		&& parse_texture(&result->texture[TEXTURE_SO], line + 2) != 0)
		free_map(&result);
	if (ft_strncmp(line, "WE", 2) == 0 \
		&& parse_texture(&result->texture[TEXTURE_WE], line + 2) != 0)
		free_map(&result);
	if (ft_strncmp(line, "EA", 2) == 0 \
		&& parse_texture(&result->texture[TEXTURE_EA], line + 2) != 0)
		free_map(&result);
	if (ft_strncmp(line, "F", 1) == 0 \
		&& result->floor_color == COLOR_UNINITIALISED)
		result->floor_color = parse_color(line + 1);
	if (ft_strncmp(line, "C", 1) == 0 \
		&& result->ceilling_color == COLOR_UNINITIALISED)
		result->ceilling_color = parse_color(line + 1);
	return (result);
}
