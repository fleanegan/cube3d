#include "../inc/cube3d.h"

static int	initialize(const char *file_name, int *width, int *height, int *fd);
int			calc_width(char *line);
int			prepare_exit(int fd, int status);

int	is_line_of_map(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]) == 1)
		i++;
	if (line[i] != '1')
		return (0);
	while (line[i] == '0' || line[i] == '1' || ft_isspace(line[i]) \
			|| is_spawn_point(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (-1);
}

int	measure_map(const char *file_name, int *height, int *width)
{
	int		fd;
	char	*line;
	int		tmp_height;
	int		in_map;
	char	*line_clean;

	in_map = 0;
	if (initialize(file_name, height, width, &fd))
		return (1);
	while (gnl(fd, &line))
	{
		if (is_line_of_map(line) == 1)
		{
			in_map = 1;
			line_clean = clean_line(line);
			tmp_height = ft_strlen(line_clean);
			free(line_clean);
			if (tmp_height < 0)
			{
				free(line);
				return (prepare_exit(fd, 1));
			}
			if (tmp_height > *height)
				*height = tmp_height;
			(*width)++;
		}
		if (is_line_of_map(line) == -1 && in_map == 1)
		{
			free(line);
			write(2, MAP_ERROR, ft_strlen(MAP_ERROR));
			return (prepare_exit(fd, 1));
		}
		free(line);
	}
	return (prepare_exit(fd, 0));
}

static int	initialize(const char *file_name, int *width, int *height, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (write(2, OPENING_FILE, ft_strlen(OPENING_FILE)));
	*height = 0;
	*width = 0;
	return (0);
}

int	prepare_exit(int fd, int status)
{
	gnl(-1, NULL);
	close(fd);
	return (status);
}
