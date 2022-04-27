#include "../inc/cube3d.h"

static int	initialize(const char *file_name, int *width, int *height, int *fd);
int			calc_width(char *line);
int			prepare_exit(int fd, int status);

int	measure_map(const char *file_name, int *height, int *width)
{
	int		fd;
	char	*line;
	int		tmp_height;

	if (initialize(file_name, height, width, &fd))
		return (-1);
	while (gnl(fd, &line))
	{
		tmp_height = calc_width(line);
		free(line);
		if (tmp_height < 0 || (*height != 0 && tmp_height != *height))
			return (prepare_exit(fd, -1));
		*height = tmp_height;
		(*width)++;
	}
	return (prepare_exit(fd, 0));
}

static int	initialize(const char *file_name, int *width, int *height, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (-1);
	*height = 0;
	*width = 0;
	return (0);
}

int	calc_width(char *line)
{
	int		tmp_width;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (! split_line)
		return (-1);
	tmp_width = (int) count_entries_in_2d_char_array(split_line);
	free_2d_array((void **)split_line);
	return (tmp_width);
}

int	prepare_exit(int fd, int status)
{
	gnl(-1, NULL);
	close(fd);
	return (status);
}
