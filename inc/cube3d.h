#ifndef CUBE3D_H
# define CUBE3D_H
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include "../lib/libft/get_next_line_bonus.h"
# include "math.h"
# include <stdio.h>
# include <float.h>
# include <fcntl.h>
# include <../lib/mlx/mlx_int.h>
# define TILE_SIZE	64.0
# define DEG2RAD 0.017453293f
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

typedef struct s_plane
{
	t_matrix	normal_vector;
	int			parallel_axis;
	t_matrix	distance_from_origin;
}	t_plane;

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
	t_img		*texture[4];
	int			len_per_unit[3];
	int 		wall_height;
	t_img		*mouse_texture;
}		t_map;

typedef struct s_ray
{
	int			x_intersection_world_coordinates;
	int			y_intersection_world_coordinates;
	int			y_max_screen_coordinates;
	int			y_min_clipped_screen_coordinates;
	int			y_max_clipped_screen_coordinates;
	int			x_clipped_screen_coordinates;
	float		distance;
	int			y_min_screen_coordinates;
	char		wall_orientation;
	t_matrix	*object_at_contact;
}	t_ray;

typedef struct s_camera
{
	float			distance_screen;
	float			angle_camera_horiz;
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

typedef struct s_mouse_gun
{
	t_matrix	pos;
	t_matrix	*target;
	t_matrix	velocity;
	float		speed_factor;
	int			is_activated;
	t_img		*texture;
	int			size_on_screen;
}	t_mouse_gun;

typedef struct s_player
{
	t_matrix	pos;
	t_matrix	orientation;
	t_movements	movements;
	int			admin_mode;
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
	t_mouse_gun		mouse_gun;
	t_map			*map;
	t_camera		camera;
}	t_data;

//init
t_player		init_player(t_map *map);
t_camera		init_camera();
int	init_mlx(t_data	*data);

//drawing
unsigned int calc_pixel_colour(const t_data *data, const t_ray *ray, int cnt);
void	draw_wall_segment(t_data *data, t_ray *ray);
unsigned int get_pixel_color_from_texture(int x, int y, const t_img *tex);
int calc_pixel_index_y(const t_ray *ray, int cnt, const t_img *tex);
int calc_pixel_index_x(const t_ray *ray, const t_img *tex, const t_data *data);
unsigned int get_pixel_color_from_texture(int x, int y, const t_img *tex);
t_img *get_texture(const t_data *data, const t_ray *ray);

// parsing
t_map			*new_map(int width, int height);
int				measure_map(const char *file_name, int *height, int *width);
t_map			*parse_map(const char *string);
int				parse_line(char *line, t_map *map, int y_act);
int				init_textures(t_data *data);

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
t_ray calc_distance_to_obstacle(t_data *data, t_matrix *dir);
int raycast_one_slice(t_data *data, int step,
					  t_ray *ray);
t_matrix	find_ray_end(\
		t_matrix *dir, const t_matrix *base, t_matrix *result, float t);
t_ray calc_distance_to_wall_matching_normal_vector(t_matrix *dir, t_data *data,
												   t_plane *wall);
int is_dir_parallel_to_obstacle_surface(t_data *data, t_matrix *intersection);
int		prepare_slice_orientation(t_data *data, int step, \
		t_matrix *slice_dir, float *cam_angle);
void calc_wall_dimensions_slice(t_data *data, int step, \
				t_matrix *dir_cam_angle, t_ray *ray);
void	clip_to_screen_limits(t_data *data, t_ray *ray);

void draw_line(t_point p0, t_point p1, t_data *img, int colour);
void			draw_1px_to_img(t_data *data, int x, int y, unsigned int color);
int				render_frame(void *void_img);

// helper functions
void			*free_map(t_map **map);
float	calc_point_distance(t_matrix *from, t_matrix *to);

// mouse gun
void	update_mouse_gun(t_data *data);
void	init_mouse_gun(t_data *data);

t_matrix 		**new_grid(t_map *map);
int				red_cross_handler(t_data *data);
void			tear_down_mlx_session(t_data *img);

//debug
void			print_matrix(t_matrix *a);
char * int2bin(int i);
#endif //CUBE3D_H
