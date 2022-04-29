/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:43:57 by                   #+#    #+#             */
/*   Updated: 2022/02/01 17:41:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	zero_init_rotation_matrix(t_matrix *t)
{
	ft_bzero(t, sizeof((*t)));
	t->height = 3;
	t->width = 3;
}

void	zero_init_point(t_matrix *p)
{
	ft_bzero(p, sizeof((*p)));
	p->height = 3;
	p->width = 1;
}

t_matrix	euler2rot(\
					double alpha_deg, double beta_deg, double gamma_deg)
{
	t_matrix	result;
	double		u;
	double		v;
	double		w;

	zero_init_rotation_matrix(&result);
	u = M_PI / 180. * alpha_deg;
	v = M_PI / 180. * beta_deg;
	w = M_PI / 180. * gamma_deg;
	result.mat[0][0] = cos(v) * cos(w);
	result.mat[0][1] = sin(u) * sin(v) * cos(w) - cos(u) * sin(w);
	result.mat[0][2] = sin(u) * sin(w) + cos(u) * sin(v) * cos(w);
	result.mat[1][0] = cos(v) * sin(w);
	result.mat[1][1] = cos(u) * cos(w) + sin(u) * sin(v) * sin(w);
	result.mat[1][2] = cos(u) * sin(v) * sin(w) - sin(u) * cos(w);
	result.mat[2][0] = -sin(v);
	result.mat[2][1] = sin(u) * cos(v);
	result.mat[2][2] = cos(u) * cos(v);
	return (result);
}

int	multiply(t_matrix *a, t_matrix *b, t_matrix *result)
{
	int			i;
	int			j;
	int			n;
	t_matrix	tmp;

	if (a->width != b->height)
		return (-1);
	zero_init_rotation_matrix(&tmp);
	tmp.width = b->width;
	tmp.height = a->height;
	j = -1;
	while (++j < a->width)
	{
		i = -1;
		while (++i < b->height)
		{
			n = -1;
			while (++n < a->width)
				tmp.mat[i][j] += a->mat[i][n] * b->mat[n][j];
		}
	}
	*result = tmp;
	return (0);
}

int	scalar_multiply(t_matrix *a, float b, t_matrix *result)
{
	int			i;
	int			j;

	ft_bzero(result->mat, 9 * sizeof(float));
	result->width = a->width;
	result->height = a->height;
	j = -1;
	while (++j < a->width)
	{
		i = -1;
		while (++i < a->height)
			result->mat[i][j] = a->mat[i][j] * b;
	}
	return (0);
}
