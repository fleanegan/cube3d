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

char	*parse_texture(t_map *result, char *line)
{
	int		i;
	int		y;

	i = 0;
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	if (i == 0)
		return (error_parsing(TEXTURE_ERROR));
	y = i;
	while (line[y] && ft_isspace(line[y]) == 0)
		y++;
	if (y > i)
		line[y] = '\0';
	return (ft_strdup(line + i));
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
	if (ft_strncmp(line, "NO", 2) == 0)
		result->texture[TEXTURE_NO] = parse_texture(line + 2);
	if (ft_strncmp(line, "SO", 2) == 0)
		result->texture[TEXTURE_SO] = parse_texture(line + 2);
	if (ft_strncmp(line, "WE", 2) == 0)
		result->texture[TEXTURE_WE] = parse_texture(line + 2);
	if (ft_strncmp(line, "EA", 2) == 0)
		result->texture[TEXTURE_EA] = parse_texture(line + 2);
	if (ft_strncmp(line, "F", 1) == 0)
		result->floor_color = parse_color(line + 1);
	if (ft_strncmp(line, "C", 1) == 0)
		result->ceilling_color = parse_color(line + 1);
	return (result);
}
