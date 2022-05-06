#include "../inc/cube3d.h"

int	is_mouse_at_target(t_data *data)
{
	int	x;
	int	y;

	x = ((int)(data->mouse_gun.pos.mat[0][0] / TILE_SIZE));
	y = ((int)(data->mouse_gun.pos.mat[1][0] / TILE_SIZE));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0 \
		|| data->mouse_gun.target == &data->map->grid[x][y])
		return (1);
	return (0);
}

float	calc_angle_player_mouse(float d_x, float d_y, t_matrix *dir)
{
	return ((atan2f(d_y, d_x) \
	- atan2f((*dir).mat[1][0], (*dir).mat[0][0])) * RAD2DEG);
}

int	is_non_transparent_pixel(const t_data *data, int px_index_x, int px_index_y)
{
	unsigned int	colour;

	colour = get_pixel_color_from_texture \
		(px_index_x, px_index_y, data->map->mouse_texture);
	if ((colour >> 24 == 0 || colour << 8 != 0))
		return (1);
	return (0);
}

t_dimension_2d	determine_drawing_area(const t_data *data, \
				const t_matrix *center_on_screen, \
				float dist_to_player, t_dimension_2d *drawing_area)
{
	float	scale;

	scale = data->camera.distance_screen / dist_to_player;
	drawing_area->y_max = center_on_screen->mat[1][0] + \
	scale * data->mouse_gun.size_on_screen / 2.f;
	drawing_area->x_max = center_on_screen->mat[0][0] + \
	scale * data->mouse_gun.size_on_screen / 2.f;
	drawing_area->x_min = \
		drawing_area->x_max - data->mouse_gun.size_on_screen * scale;
	drawing_area->y_min = \
		drawing_area->y_max - data->mouse_gun.size_on_screen * scale;
	return (*drawing_area);
}

void	set_idle_mouse_position(t_data *data, t_mouse_gun *mg)
{
	t_matrix	idle_pos;

	mg->pos = data->player.pos;
	zero_init_point(&idle_pos);
	idle_pos.mat[0][0] = 50.f;
	idle_pos.mat[1][0] = 10.f;
	multiply(&data->player.orientation, &idle_pos, &idle_pos);
	mg->pos.mat[0][0] += idle_pos.mat[0][0];
	mg->pos.mat[1][0] += idle_pos.mat[1][0];
}
