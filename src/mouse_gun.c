#include "../inc/cube3d.h"

void draw_mouse_pixel(t_data *data, t_matrix *mouse_position_on_screen,
					  float distance_player_mouse);

int	is_mouse_at_target(t_data *data)
{
	int	x;
	int	y;

	x = ((int)(data->mouse_gun.pos.mat[0][0] / TILE_SIZE));
	y = ((int)(data->mouse_gun.pos.mat[1][0] / TILE_SIZE));
	if (x >= data->map->width || x < 0 || y >= data->map->height || y < 0\
		|| data->mouse_gun.target == &data->map->grid[x][y])
		return (1);
	return (0);
}

void	draw_mouse_gun(t_data *data)
{
	float	angle_player_mouse;
	float	d_x;
	float	d_y;
	float	distance_player_mouse;
	t_matrix	mouse_position_on_screen;
	t_matrix	dir;

	generate_direction_vector(&data->player.orientation, &dir);
	d_x = data->mouse_gun.pos.mat[0][0] - data->player.pos.mat[0][0];
	d_y = data->mouse_gun.pos.mat[1][0] - data->player.pos.mat[1][0];
	distance_player_mouse = sqrtf(powf(d_x, 2) + powf(d_y, 2));
	angle_player_mouse = (atan2f(d_y, d_x) - atan2f(dir.mat[1][0], dir.mat[0][0])) * RAD2DEG;
	mouse_position_on_screen.mat[0][0] = data->camera.win_size.x_max * (0.5f + (angle_player_mouse / (data->camera.angle_camera_horizontal)));
	draw_mouse_pixel(data, &mouse_position_on_screen, distance_player_mouse);
}

void draw_mouse_pixel(t_data *data, t_matrix *mouse_position_on_screen,
					  float distance_player_mouse)
{
	int		dummy_size = 15;
	float	scale;
	int		x;
	int		y;
	int		px_index_x;
	int		px_index_y;
	float	y_max;
	float	x_max;
	float	x_min;
	float	y_min;

	scale = data->camera.distance_screen / distance_player_mouse;
	y_max = data->camera.win_size.y_max / 2.f + scale * dummy_size / 2.f;
	x_max = mouse_position_on_screen->mat[0][0] + scale * dummy_size / 2.f;
	x_min = mouse_position_on_screen->mat[0][0] - scale * dummy_size / 2.f;
	y_min = y_max - dummy_size * scale;
	y = y_min;
	while (y > 0 && y < data->camera.win_size.y_max && y < y_max)
	{
		x = x_min;
		while (x < data->camera.win_size.x_max && x > 0 && x < x_max)
		{
			px_index_x = (int)(((float)x - x_min) / (x_max - x_min) * (float)data->map->mouse_texture->width);
			px_index_y = (int)(((float)y - y_min) / (y_max - y_min) * (float)data->map->mouse_texture->height);
//			printf("xm: %f, xma: %f, ym: %f, yma: %f, x: %d, y: %d, pxx: %d, pxy: %d\n", x_min, x_max, y_min, y_max, x, y, px_index_x, px_index_y);
			if (px_index_x > 0 && px_index_x < data->map->mouse_texture->width && px_index_y > 0 && px_index_y < data->map->mouse_texture->height)
				draw_1px_to_img(data, x, y, get_pixel_color_from_texture(px_index_x, px_index_y, data->map->mouse_texture));
			x++;
		}
		y++;
	}
//	puts("new dist");
	(void) scale;
}

void	init_mouse_gun(t_data *data)
{
	t_mouse_gun	*mg;
	float		distance;
	t_matrix	player_mouse_vector;

	mg = &data->mouse_gun;
	zero_init_point(&player_mouse_vector);
	player_mouse_vector.mat[0][0] = (mg->target->mat[0][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[0][0]);
	player_mouse_vector.mat[1][0] = (mg->target->mat[1][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[1][0]);
	player_mouse_vector.mat[2][0] = (mg->target->mat[2][0] * TILE_SIZE + TILE_SIZE / 2.f - mg->pos.mat[2][0]);
	distance = sqrtf(powf(player_mouse_vector.mat[0][0], 2) + powf(player_mouse_vector.mat[1][0], 2) + powf(player_mouse_vector.mat[2][0], 2));
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
		mg->pos.mat[0][0] +=  mg->velocity.mat[0][0] * 10;
		mg->pos.mat[1][0] +=  mg->velocity.mat[1][0] * 10;
		mg->pos.mat[2][0] +=  mg->velocity.mat[2][0] * 10;
		draw_mouse_gun(data);
	}
	else
		mg->pos = data->player.pos;
}
