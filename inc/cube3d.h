/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:09 by                   #+#    #+#             */
/*   Updated: 2022/02/01 18:18:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include "../lib/libft/get_next_line_bonus.h"
# include "math.h"
# include <fcntl.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}		t_point;

typedef struct s_dimension_2d
{
	int	x_max;
	int	x_min;
	int	y_max;
	int	y_min;
}		t_dimension_2d;

typedef struct s_map
{
	t_matrix	**grid;
	int			width;
	int			height;
}		t_map;

typedef struct s_data {
	void				*img;
	char				*addr;
	void				*mlx;
	void				*mlx_win;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_dimension_2d		win_size;
	t_matrix			orientation;
	t_map				*map;
	float				z_scale;
	float				x_offset;
	float				y_offset;
	float				zoom;
}	t_data;

// parsing
t_map			*new_map(int width, int height);
void			init_view(t_data *img);
int				measure_map(const char *file_name, int *width, int *height);
t_map			*parse_map(const char *string);
int				parse_line(char *line, t_map *map, int y_act);

// drawing
void			turn_all_pixels_black(t_data *img);
void			draw_line(t_point p0, t_point p1, t_data *img);
void			draw_1px_to_img(t_data *data, int x, int y, int color);
int				render_frame(void *void_img);

// helper functions
void			*free_map(t_map **map);
void			set_point(t_point *pt, double x, double y, double z);
t_matrix ** new_grid(t_map *map);
int				key_handler(int keycode, t_data *img);
void			tear_down_mlx_session(t_data *img);

#endif //FDF_H
