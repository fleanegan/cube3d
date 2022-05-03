#ifndef CUBE3D_H
# define CUBE3D_H
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include "../lib/libft/get_next_line_bonus.h"
# include "math.h"
# include <stdio.h>
# include <float.h>
# include <fcntl.h>
# define TILE_SIZE	64.0
# define RAD2DEG 360.0/M_PI/2.0
# define DEG2RAD M_PI/360.0*2.0

// key

# define KEY_UP 122
# define KEY_DOWN 115
# define KEY_LEFT 113
# define KEY_RIGHT 100
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_RIGHT 65363
# define KEY_ESC 65307

# define BAD_FILE_NAME "Error\nBad file name (*.cub)\n"
# define OPENING_FILE "Error\nOpening file fail\n"
# define MALLOC_FAIL "Error\nMalloc fail\n"
# define TEXTURE_ERROR "Error\nBad format for texture\n"

# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3

# define COLOR_OUT_OF_RANGE -2
# define COLOR_UNINITIALISED -1

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
	int 		tile_size;
	char		*texture[4];
	int			ceilling_color;
	int			floor_color;
}		t_map;

typedef struct s_camera
{
	float			distance_screen;
	float			angle_camera;
	t_dimension_2d	win_size;
}	t_camera;

typedef struct s_player
{
	t_matrix	pos;
	t_matrix	orientation;
}	t_player;

typedef struct s_mlx {
	void *img;
	char *addr;
	void *mlx;
	void *mlx_win;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_mlx;

typedef struct s_data {
	t_mlx			mlx;
	t_player		player;
	t_map			*map;
	t_camera		camera;
}	t_data;

//init
t_player		init_player(t_map *map);
t_camera		init_camera(void);
t_map			*init_map(void);

// parsing
t_map			*new_map(int width, int height);
int				measure_map(const char *file_name, int *height, int *width);
t_map			*parse_map(const char *string);
t_map			*parse(const char *file_name);
int				parse_line(char *line, t_map *map, int y_act);
t_map			*parse_infos(t_map *result, char *line);
void			*error_parsing(char *str);

int				is_cub_file(const char *file_name);

// raycasting
int 			generate_direction_vector(\
				t_matrix *orientation_AnnE, t_matrix *result);
float			calc_distance_to_obstacle(t_data *data, t_matrix *dir);
int 			calc_column_dimensions(t_data *data, int step, t_point *p0, t_point *p1);

// drawing
void			turn_all_pixels_black(t_data *img);
void			draw_line(t_point p0, t_point p1, t_data *img);
void			draw_1px_to_img(t_data *data, int x, int y, int color);
int				render_frame(void *void_img);

// helper functions
void			*free_map(t_map **map);
void			set_point(t_point *pt, double x, double y, double z);
t_matrix 		**new_grid(t_map *map);
int				key_handler(int keycode, t_data *img);
int				red_cross_handler(t_data *data);
void			tear_down_mlx_session(t_data *img);

// math extensions
float			calc_point_distance(t_matrix *from, t_matrix *to);

//debug
void 			print_matrix(t_matrix *a);
void			print_map_infos(t_map *map);
#endif //FDF_H
