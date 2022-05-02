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
# define DEG2RAD 0.0175f
# define RAD2DEG 57.295779513f

// key

# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_LEFT 97
# define KEY_RIGHT 100
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_UP 65362
# define KEY_ARROW_DOWN 65364
# define KEY_ESC 65307

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
	int			len_per_unit[3];
	int 		wall_height;
}		t_map;

typedef struct s_camera
{
	float			distance_screen;
	float			angle_camera_horizontal;
	float			angle_camera_vertical;
	t_dimension_2d	win_size;
}	t_camera;

typedef struct s_movements
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rot_up;
	int	rot_down;
	int	rot_right;
	int	rot_left;
}	t_movements;

typedef struct s_player
{
	t_matrix	pos;
	t_matrix	orientation;
	t_movements	movements;
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
t_camera		init_camera();

// parsing
t_map			*new_map(int width, int height);
int				measure_map(const char *file_name, int *height, int *width);
t_map			*parse_map(const char *string);
int				parse_line(char *line, t_map *map, int y_act);

// movements
void			move(t_data *data);
void			rotate(t_data *data);

// event handling
int handle_key_press(int keycode, t_data *data);
int handle_key_release(int keycode, t_data *data);
int				red_cross_handler(t_data *data);

// raycasting
int				generate_direction_vector(\
				t_matrix *orientation, t_matrix *result);
float			calc_distance_to_obstacle(t_data *data, t_matrix *dir);
int				calc_column_dimensions(t_data *data, int step, t_point *p0, t_point *p1);

// drawing
void			turn_all_pixels_black(t_data *data);
void draw_line(t_point p0, t_point p1, t_data *img, int colour);
void			draw_1px_to_img(t_data *data, int x, int y, int color);
int				render_frame(void *void_img);

// helper functions
void			*free_map(t_map **map);
void			set_point(t_point *pt, double x, double y, double z);

t_matrix 		**new_grid(t_map *map);
int				key_handler(int keycode, t_data *img);
void			tear_down_mlx_session(t_data *img);

// math extensions
float			calc_point_distance(t_matrix *from, t_matrix *to);

//debug
void			print_matrix(t_matrix *a);
#endif //CUBE3D_H
