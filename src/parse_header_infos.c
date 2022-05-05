#include "../inc/cube3d.h"

int	line_is_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0');
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
	if (line[y + 1] != '\0')
		return (write(2, TEXTURE_ERROR, ft_strlen(TEXTURE_ERROR)));
	*dest = ft_strdup(line + i);
	if (*dest == NULL)
		return (write(2, MALLOC_FAIL, ft_strlen(MALLOC_FAIL)));
	return (0);
}
char	*go_next_field(char *line)
{
	char	*tmp;

	tmp = ft_strchr(line, ',');
	if (tmp == NULL)
	{
		write(2, COLOR_FAIL, ft_strlen(COLOR_FAIL));
		return (NULL);
	}
	tmp++;
	return (tmp);
}

int	parse_color(int *dest, char *line)
{
	int		r;
	int		g;
	int		b;

	if (*dest != COLOR_UNINITIALISED)
		return (write(2, COLOR_DUPLICATE, ft_strlen(COLOR_DUPLICATE)));
	r = ft_atoi(line);
	if (r < 0 || r > 255)
		return (write(2, COLOR_OUT_OF_RANGE, ft_strlen(COLOR_OUT_OF_RANGE)));
	line = go_next_field(line);
	if (line == NULL)
		return (1);
	g = ft_atoi(line);
	if (g < 0 || g > 255)
		return (write(2, COLOR_OUT_OF_RANGE, ft_strlen(COLOR_OUT_OF_RANGE)));
	line = go_next_field(line);
	if (line == NULL)
		return (1);
	b = ft_atoi(line);
	while (*line && ft_isdigit(*line) == 1)
		line++;
	if (*line != '\n')
		return (write(2, COLOR_FAIL, ft_strlen(COLOR_FAIL)));
	if (b < 0 || b > 255)
		return (write(2, COLOR_OUT_OF_RANGE, ft_strlen(COLOR_OUT_OF_RANGE)));
	*dest = r << 16 | g << 8 | b;
	return (0);
}

void	parse_infos(t_map **result, char *line)
{
	if ((ft_strncmp(line, "NO", 2) == 0 \
			&& parse_texture(&(*result)->texture[TEXTURE_NO], line + 2) == 0) \
		|| (ft_strncmp(line, "SO", 2) == 0 \
			&& parse_texture(&(*result)->texture[TEXTURE_SO], line + 2) == 0) \
		|| (ft_strncmp(line, "WE", 2) == 0 \
			&& parse_texture(&(*result)->texture[TEXTURE_WE], line + 2) == 0) \
		|| (ft_strncmp(line, "EA", 2) == 0 \
			&& parse_texture(&(*result)->texture[TEXTURE_EA], line + 2) == 0) \
		|| (ft_strncmp(line, "F", 1) == 0 \
			&& parse_color(&(*result)->floor_color, line + 1) == 0) \
		|| (ft_strncmp(line, "C", 1) == 0 \
			&& parse_color(&(*result)->ceilling_color, line + 1) == 0))
		return ;
	if (line_is_only_space(line) == 0)
		free_map(result);
}
