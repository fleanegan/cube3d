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
# include <stdio.h>
# include <fcntl.h>
# define TILE_SIZE	64.0
# define RAD2DEG 360.0/M_PI/2.0
# define DEG2RAD M_PI/360.0*2.0

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
	t_matrix	*spawn_point;
	int			width;
	int			height;
	char		spawn_orientation;
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

typedef struct s_game_obj
{
	int			tile_width;
	int			tile_height;
	t_matrix	pos;
	t_matrix	orientation;
	t_map		*map;
}	t_game_obj;

//init
t_game_obj		init_game_obj(t_map *map);

// parsing
t_map			*new_map(int width, int height);
int				measure_map(const char *file_name, int *height, int *width);
t_map			*parse_map(const char *string);
int				parse_line(char *line, t_map *map, int y_act);

// raycasting
int 			generate_direction_vector(\
				t_game_obj *game_obj, t_matrix *result);
float			calc_distance_to_wall(t_matrix *dir, t_game_obj *game_obj);

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
