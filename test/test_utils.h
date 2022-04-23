#ifndef TEST_UTILS_H
# define TEST_UTILS_H

#include "gtest/gtest.h"
extern "C" {
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../inc/cube3d.h"
# include "../lib/libft/libft.h"
# include <ctype.h>
# include <string.h>
# include <limits.h>
}

void expect_point_eq(t_matrix *in, float x, float y, float z)
{
	EXPECT_FLOAT_EQ(in->mat[0][0], x);
	EXPECT_FLOAT_EQ(in->mat[1][0], y);
	EXPECT_FLOAT_EQ(in->mat[2][0], z);
}

void expect_matrix_eq(t_matrix ours, t_matrix theirs)
{
	EXPECT_FLOAT_EQ(ours.mat[0][0], theirs.mat[0][0]);
	EXPECT_FLOAT_EQ(ours.mat[0][1], theirs.mat[0][1]);
	EXPECT_FLOAT_EQ(ours.mat[0][2], theirs.mat[0][2]);
	EXPECT_FLOAT_EQ(ours.mat[1][0], theirs.mat[1][0]);
	EXPECT_FLOAT_EQ(ours.mat[1][1], theirs.mat[1][1]);
	EXPECT_FLOAT_EQ(ours.mat[1][2], theirs.mat[1][2]);
	EXPECT_FLOAT_EQ(ours.mat[2][0], theirs.mat[2][0]);
	EXPECT_FLOAT_EQ(ours.mat[2][1], theirs.mat[2][1]);
	EXPECT_FLOAT_EQ(ours.mat[2][2], theirs.mat[2][2]);
}

void print_matrix(t_matrix *a)
{
	int					x;
	int					y;

	y = 0;
	printf("height %d width %d\n", a->height, a->width);
	while (y < a->height)
	{
		x = 0;
		while (x < a->width)
		{
			printf("%f ", a->mat[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

#endif	 // TEST_UTILS_H
