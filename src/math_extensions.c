/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_extensions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:02:52 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:02:54 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

float	calc_point_distance(t_matrix *from, t_matrix *to)
{
	float	sqrd_d;
	int		i;

	i = 0;
	sqrd_d = 0;
	while (i < 3)
	{
		sqrd_d += powf(from->mat[i][0] - to->mat[i][0], 2.);
		i++;
	}
	return (sqrtf(sqrd_d));
}

int	generate_direction_vector(t_matrix *orientation_AnnE, t_matrix *result)
{
	t_matrix	dir_init;

	zero_init_point(result);
	zero_init_point(&dir_init);
	dir_init.mat[0][0] = 1;
	dir_init.mat[1][0] = 0;
	if (multiply(orientation_AnnE, &dir_init, result))
	{
		printf("matrix multiplication failed\n");
		return (1);
	}
	return (0);
}
