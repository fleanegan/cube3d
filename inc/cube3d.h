/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:01:19 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:01:58 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line_bonus.h"
# include "math.h"
# include <stdio.h>
# include <float.h>
# include <fcntl.h>
# include <../lib/mlx/mlx_int.h>
# ifndef TESTING
#  include <../lib/mlx/mlx.h>
# endif
# define TILE_SIZE 64.0f
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

// error
# define BAD_FILE_NAME "Error\nBad file name (*.cub)\n"
# define OPENING_FILE "Error\nOpening file fail\n"
# define MALLOC_FAIL "Error\nMalloc fail\n"
# define TEXTURE_ERROR "Error\nBad format for texture\n"
# define TEXTURE_DUPLICATE "Error\nMultiple texture for same orientation\n"
# define COLOR_FAIL "Error\nBad format for color\n"
# define COLOR_DUPLICATE "Error\nMultiple color for same field\n"
# define COLOR_OUT_OF_RANGE "Error\nColor is out of range\n"
# define COLOR_UNINITIALISED -1
# define MAP_ERROR "Error\nBad format for the map\n"
# define ERROR_MULTIPLE_SPAWNPOINT "Error\nMultiple spawn points\n"

# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3

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
	char		*texture_name[4];
	int			wall_height;
	t_img		*mouse_texture;
	int			c_color;
	int			f_color;
}		t_map;

typedef struct s_ray
{
	int			x_intersection_world;
	int			y_intersection_world;
	int			y_max_screen_coordinates;
	int			y_min_clipped_screen;
	int			y_max_clipped_screen;
	int			x_clipped_screen;
	float		distance;
	int			y_min_screen;
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
	float		distance;
	int			is_activated;
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
	void	*img;
	char	*addr;
	void	*mlx;
	void	*mlx_win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
t_camera		init_camera(void);
int				init_mlx(t_data *d);

//drawing
unsigned int	calc_pixel_colour(\
					const t_data *data, const t_ray *ray, int cnt);
void			draw_wall_segment(t_data *data, t_ray *ray);
unsigned int	get_pixel_color_from_texture(int x, int y, const t_img *tex);
int				calc_pixel_index_y(const t_ray *ray, int cnt, const t_img *tex);
int				calc_pixel_index_x(\
					const t_ray *ray, const t_img *tex, const t_data *data);
unsigned int	get_pixel_color_from_texture(int x, int y, const t_img *tex);
t_img			*get_texture(const t_data *data, const t_ray *ray);
void			draw_map(t_data *data);
t_camera		init_camera(void);
t_map			*init_map(const char *file_name);

// parsing
int				measure_map(const char *file_name, int *height, int *width);
t_map			*parse_map(const char *string);
int				init_textures(t_data *data);
int				check_map(t_map *map);
int				spawn_is_set(t_map *result);

// movements
void			move(t_data *data);
void			rotate(t_data *data);

// event handling
int				handle_key_press(int keycode, t_data *data);
int				handle_key_release(int keycode, t_data *data);
int				red_cross_handler(t_data *data);
int				is_line_of_map(char *line);
t_map			*parse(const char *file_name);
int				parse_map_line(char *line, t_map **map, int y_act);
void			parse_infos(t_map **result, char *line);
void			*error_parsing(t_map **result, char *str);
int				is_spawn_point(char c);
char			*clean_line(char *line);
int				header_infos_are_set(t_map *result);
int				is_cub_file(const char *file_name);
int				line_is_only_space(char *line);

// raycasting
int				generate_direction_vector(\
					t_matrix *orientation, t_matrix *result);
t_ray			calc_distance_to_nearest_wall(t_data *data, t_matrix *dir);
int				raycast_one_slice(t_data *data, int step, t_ray *ray);
t_matrix		find_ray_end(t_matrix *dir, \
					const t_matrix *base, t_matrix *result, float t);
t_ray			calc_distance_to_wall(t_matrix *dir, t_data *data,
					t_plane *wall);
int				is_dir_parallel_to_obstacle_surface(\
				t_data *data, t_matrix *intersection);
int				prepare_slice_orientation(t_data *data, int step, \
					t_matrix *slice_dir, float *cam_angle);
void			calc_wall_dimensions_slice(t_data *data, int step, \
					t_matrix *dir_cam_angle, t_ray *ray);
void			clip_to_screen_limits(t_data *data, t_ray *ray);
t_matrix		*get_object_at_contact(\
					t_matrix *intersection, t_data *data, t_plane *wall);
void			update_ray(t_data *data, t_plane *wall, \
					t_ray *result, t_matrix *intersection);
t_matrix		find_intersection_with_wall_candidate(t_matrix *dir, \
					const t_data *data, const t_plane *wall, int distance_wall);
void			draw_1px_to_img(t_data *data, int x, int y, unsigned int color);
int				render_frame(void *void_img);
void			init_points_to_wall(const t_map *map, t_matrix *const *result);

// helper functions
void			*free_map(t_map **map);
float			calc_point_distance(t_matrix *from, t_matrix *to);
void			free_textures(t_data *data);
int				print_error(char *msg);

// mouse gun
void			update_mouse_gun(t_data *data);
void			init_mouse_gun(t_data *data, t_ray *ray);
void			remove_interior_walls(t_data *data);
void			put_texture_on_screen(t_data *data, \
					t_matrix *center_on_screen, float dist_to_player);
t_dimension_2d	determine_drawing_area(const t_data *data, \
					const t_matrix *center_on_screen, \
					float dist_to_player, t_dimension_2d *drawing_area);
float			calc_angle_player_mouse(float d_x, float d_y, t_matrix *dir);
void			set_idle_mouse_position(t_data *data, t_mouse_gun *mg);
int				is_mouse_at_target(t_data *data);
int				is_non_transparent_pixel(\
					const t_data *data, int px_index_x, int px_index_y);
t_matrix		**new_grid(t_map *map);
int				red_cross_handler(t_data *data);
void			tear_down_mlx_session(t_data *img, int exit_code);

//debug
void			print_matrix(t_matrix *a);
void			print_map_infos(t_map *map);
#endif //CUBE3D_H
