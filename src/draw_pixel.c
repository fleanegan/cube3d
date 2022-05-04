#include "../inc/cube3d.h"

int calc_pixel_index_y(const t_ray *ray, int cnt, const t_img *tex);
int calc_pixel_index_x(const t_ray *ray, const t_img *tex);
unsigned int get_pixel_color_from_texture(int x, int y, const char *current,
										  const t_img *tex);

unsigned int calc_pixel_colour(const t_data *data, const t_ray *ray, int cnt)
{
	int				x;
	int				y;
	unsigned int	colour;
	const char		*current;
	t_img			*tex;

	colour = 0;
	if (ray->wall_orientation == 'N')
	{
		//todo: incorporate defines after merge
		tex = data->map->texture[0];
		x = calc_pixel_index_x(ray, tex);
		y = calc_pixel_index_y(ray, cnt, tex);
		if (x >= 0)
			colour = get_pixel_color_from_texture(x, y, current, tex);
	}
	return colour;
}

unsigned int get_pixel_color_from_texture(int x, int y, const char *current,
										  const t_img *tex)
{
	unsigned int colour;
	current = &tex->data[x * tex->bpp / 8 + tex->width * y * tex->bpp / 8];
	colour = current[0] << 24 | current[1] << 16 | current[2] << 8 | current[3];
	return colour;
}

int calc_pixel_index_x(const t_ray *ray, const t_img *tex)
{
	int	x;

	x = (int) ((float) (ray->x_intersection_world_coordinates \
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

void	draw_1px_to_img(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->mlx.addr \
		+ (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}