#include "../inc/cube3d.h"

int	update_above(t_point *p0, t_point *pd, t_point *ps, int err)
{
	err += (int)(*pd).y;
	p0->x += (*ps).x;
	return (err);
}

int	update_below(t_point *p0, t_point *pd, t_point *ps, int err)
{
	err += (int)(*pd).x;
	p0->y += (*ps).y;
	return (err);
}

int	make_color(t_point *p0, t_point *p1)
{
	int		i;
	double	altitude;

	if (p0->z > p1->z)
		altitude = (int) p0->z;
	else
		altitude = (int) p1->z;
	altitude = sqrt(fabs(altitude)) * 105. / sqrt(500) + 50;
	if (altitude > 255.)
		altitude = 255.;
	i = (int)(255 - altitude) << 16;
	i = i | (int)altitude << 8;
	i = i | (int)(altitude);
	return (i);
}

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	t_point	pd;
	t_point	ps;
	int		err;
	int		err2;

	pd.x = (int) ft_abs((int) p1.x - (int) p0.x);
	pd.y = (int) -ft_abs((int) p1.y - (int) p0.y);
	ps.x = 1 - 2 * (p0.x >= p1.x);
	ps.y = 1 - 2 * (p0.y >= p1.y);
	err = (int) pd.x + (int) pd.y;
	while (1)
	{
		if (p0.x < 0 || p0.y < 0 || p0.x >= img->camera.win_size.x_max \
			|| p0.y >= img->camera.win_size.y_max)
			return ;
		draw_1px_to_img(img, (int) p0.x, (int) p0.y, make_color(&p0, &p1));
		err2 = 2 * err;
		if (((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y) \
		|| (p0.x == p1.x && err2 >= pd.y) || (err2 <= pd.x && p0.y == p1.y))
			break ;
		if (err2 >= pd.y)
			err = update_above(&p0, &pd, &ps, err);
		if (err2 <= pd.x)
			err = update_below(&p0, &pd, &ps, err);
	}
}
