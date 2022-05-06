#include "../inc/cube3d.h"

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
	mouse_position_on_screen.mat[1][0] = data->camera.win_size.y_max \
			/ (1.2f + (.5f * distance_player_mouse / data->mouse_gun.distance));
	put_texture_on_screen(\
	data, &mouse_position_on_screen, distance_player_mouse);
}

void	init_mouse_gun(t_data *data, t_ray *ray)
{
	t_mouse_gun	*mg;
	t_matrix	tm;

	mg = &data->mouse_gun;
	mg->is_activated = 1;
	mg->size_on_screen = 15;
	mg->target = ray->object_at_contact;
	zero_init_point(&tm);
	tm.mat[0][0] = \
	(mg->target->mat[0][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[0][0]);
	tm.mat[1][0] = \
	(mg->target->mat[1][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[1][0]);
	tm.mat[2][0] = \
	(mg->target->mat[2][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[2][0]);
	mg->distance = sqrtf(\
	powf(tm.mat[0][0], 2) + powf(tm.mat[1][0], 2) + powf(tm.mat[2][0], 2));
	scalar_multiply(&tm, 1.f / mg->distance, &mg->velocity);
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
			mg->is_activated = 0;
			mg->target->mat[2][0] = 0;
		}
		mg->pos.mat[0][0] += mg->velocity.mat[0][0] * 10;
		mg->pos.mat[1][0] += mg->velocity.mat[1][0] * 10;
		mg->pos.mat[2][0] += mg->velocity.mat[2][0] * 10;
	}
	else
		set_idle_mouse_position(data, mg);
	draw_mouse_gun(data);
}

void	put_texture_on_screen(t_data *data, \
		t_matrix *center_on_screen, float dist_to_player)
{
	int				x;
	int				y;
	int				px_index_x;
	int				px_index_y;
	t_dimension_2d	da;

	da = determine_drawing_area(data, center_on_screen, dist_to_player, &da);
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
			if (is_non_transparent_pixel(data, px_index_x, px_index_y))
				draw_1px_to_img(data, x, y, get_pixel_color_from_texture(\
					px_index_x, px_index_y, data->map->mouse_texture));
			x++;
		}
		y++;
	}
}
