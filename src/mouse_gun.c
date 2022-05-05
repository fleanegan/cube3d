#include "../inc/cube3d.h"

void			draw_mouse_pixel(t_data *data, \
				t_matrix *center_on_screen, float dist_to_player);
t_dimension_2d	determin_drawing_area(const t_data *data, \
				const t_matrix *center_on_screen, \
				float dist_to_player, t_dimension_2d *drawing_area);
float			calc_angle_player_mouse(float d_x, float d_y, t_matrix *dir);

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

void	draw_mouse_gun(t_data *data)
{
	float		d_x;
	float		d_y;
	float		distance_player_mouse;
	t_matrix	mouse_position_on_screen;
	t_matrix	dir;

	generate_direction_vector(&data->player.orientation, &dir);
	d_x = data->mouse_gun.pos.mat[0][0] - data->player.pos.mat[0][0];
	d_y = data->mouse_gun.pos.mat[1][0] - data->player.pos.mat[1][0];
	distance_player_mouse = sqrtf(powf(d_x, 2) + powf(d_y, 2));
	mouse_position_on_screen.mat[0][0] = data->camera.win_size.x_max \
		* (.5f + (calc_angle_player_mouse(d_x, d_y, &dir) \
		/ (data->camera.angle_camera_horiz)));
	mouse_position_on_screen.mat[1][0] = data->camera.win_size.y_max / 2.f;
	draw_mouse_pixel(data, &mouse_position_on_screen, distance_player_mouse);
}

float	calc_angle_player_mouse(float d_x, float d_y, t_matrix *dir)
{
	return ((atan2f(d_y, d_x) \
	- atan2f((*dir).mat[1][0], (*dir).mat[0][0])) * RAD2DEG);
}

void	draw_mouse_pixel(t_data *data, \
		t_matrix *center_on_screen, float dist_to_player)
{
	int				x;
	int				y;
	int				px_index_x;
	int				px_index_y;
	t_dimension_2d	da;

	da = determin_drawing_area(data, center_on_screen, dist_to_player, &da);
	y = da.y_min;
	while (y > 0 && y < data->camera.win_size.y_max && y < da.y_max)
	{
		x = da.x_min;
		while (x < data->camera.win_size.x_max && x > 0 && x < da.x_max)
		{
			px_index_x = (int)(((float)x - da.x_min) / (da.x_max - da.x_min) \
				* (float)data->map->mouse_texture->width);
			px_index_y = (int)(((float)y - da.y_min) / (da.y_max - da.y_min) \
				* (float)data->map->mouse_texture->height);
			draw_1px_to_img(data, x, y, get_pixel_color_from_texture(\
				px_index_x, px_index_y, data->map->mouse_texture));
			x++;
		}
		y++;
	}
}

t_dimension_2d	determin_drawing_area(const t_data *data, \
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

void	init_mouse_gun(t_data *data)
{
	t_mouse_gun	*mg;
	float		distance;
	t_matrix	player_mouse_vector;

	mg = &data->mouse_gun;
	mg->size_on_screen = 15;
	zero_init_point(&player_mouse_vector);
	player_mouse_vector.mat[0][0] = \
	(mg->target->mat[0][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[0][0]);
	player_mouse_vector.mat[1][0] = \
	(mg->target->mat[1][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[1][0]);
	player_mouse_vector.mat[2][0] = \
	(mg->target->mat[2][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[2][0]);
	distance = sqrtf(\
		powf(player_mouse_vector.mat[0][0], 2) \
		+ powf(player_mouse_vector.mat[1][0], 2) \
		+ powf(player_mouse_vector.mat[2][0], 2));
	scalar_multiply(&player_mouse_vector, 1.f / distance, &mg->velocity);
}

void	update_mouse_gun(t_data *data)
{
	t_matrix	new_pos;
	t_mouse_gun	*mg;

	mg = &data->mouse_gun;
	zero_init_point(&new_pos);
	if (mg->is_activated)
	{
		if (is_mouse_at_target(data))
		{
			puts("arrived");
			mg->is_activated = 0;
			mg->target->mat[2][0] = 0;
		}
		mg->pos.mat[0][0] += mg->velocity.mat[0][0] * 10;
		mg->pos.mat[1][0] += mg->velocity.mat[1][0] * 10;
		mg->pos.mat[2][0] += mg->velocity.mat[2][0] * 10;
		draw_mouse_gun(data);
	}
	else
		mg->pos = data->player.pos;
}
