#include "../inc/cube3d.h"

int calc_pixel_index_y(const t_ray *ray, int cnt, const t_img *tex);
int calc_pixel_index_x(const t_ray *ray, const t_img *tex, const t_data *data);
unsigned int get_pixel_color_from_texture(int x, int y, const t_img *tex);

t_img *get_texture(const t_data *data, const t_ray *ray);

unsigned int calc_pixel_colour(const t_data *data, const t_ray *ray, int cnt)
{
	int				x;
	int				y;
	unsigned int	colour;
	t_img			*tex;

	colour = 0;
	tex = get_texture(data, ray);
	x = calc_pixel_index_x(ray, tex, data);
	y = calc_pixel_index_y(ray, cnt, tex);
	if (x >= 0 && y >= 0)
		colour = get_pixel_color_from_texture(x, y, tex);
	return colour;
}

t_img *get_texture(const t_data *data, const t_ray *ray)
{
	//todo: incorporate defines after merge
	t_img *tex;
	tex = data->map->texture[0];
	if (ray->wall_orientation == 'E')
		tex = data->map->texture[1];
	if (ray->wall_orientation == 'W')
		tex = data->map->texture[2];
	if (ray->wall_orientation == 'S')
		tex = data->map->texture[3];
	return tex;
}

unsigned int get_pixel_color_from_texture(int x, int y, const t_img *tex)
{
	unsigned int	colour;
	char			*current;

	current = &tex->data[x * tex->bpp / 8 + tex->width * y * tex->bpp / 8];
	colour = current[0] << 24 | current[1] << 16 | current[2] << 8 | current[3];
	return colour;
}

int calc_pixel_index_x(const t_ray *ray, const t_img *tex, const t_data *data)
{
	int	x;

	if (ray->wall_orientation == 'S')
		x = (int) ((float) (ray->x_intersection_world_coordinates \
		% (int) TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	if (ray->wall_orientation == 'N')
		x = (int) ((float) ((int)((float)data->map->width * TILE_SIZE - ray->x_intersection_world_coordinates) \
		% (int) TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	if (ray->wall_orientation == 'W')
		x = (int) ((float) (ray->y_intersection_world_coordinates \
		% (int) TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	if (ray->wall_orientation == 'E')
		x = (int) ((float) ((int)((float)data->map->height * TILE_SIZE - ray->y_intersection_world_coordinates) \
		% (int) TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	return x;
}

int calc_pixel_index_y(const t_ray *ray, int cnt, const t_img *tex)
{
	int y;
	int	clipped_headroom;
	int	wall_height_screen_coordinates;
	wall_height_screen_coordinates = \
		ray->y_max_screen_coordinates - ray->y_min_screen_coordinates;
	clipped_headroom = \
		ray->y_min_clipped_screen_coordinates - ray->y_min_screen_coordinates;
	y = (int)((float)tex->height \
		/ (float)wall_height_screen_coordinates \
		* ((float)cnt + (float) clipped_headroom));
	return y;
}
