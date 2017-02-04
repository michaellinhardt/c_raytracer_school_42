/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 17:12:59 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/04 13:54:19 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			abstract(unsigned char *t, int rowstride, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 1;
	nbr[0][1] = 0;
	nbr[0][2] = 0;
	nbr[0][3] = 0;
	nbr[1][0] = 0;
	nbr[1][1] = 1;
	nbr[1][2] = 0;
	nbr[1][3] = 0;
	nbr[2][0] = 0;
	nbr[2][1] = 0;
	nbr[2][2] = 1;
	nbr[2][3] = 0;
	while ((index += 3) < W_Y * rowstride)
	{
		col[0] = t[index + 0];
		col[1] = t[index + 1];
		col[2] = t[index + 2];
		t[index + 0] = change_col(col, nbr[0]);
		t[index + 1] = change_col(col, nbr[1]);
		t[index + 2] = change_col(col, nbr[2]);
	}
}

void			antialiasing(unsigned char *t, int rowstride, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 1;
	nbr[0][1] = 0;
	nbr[0][2] = 0;
	nbr[0][3] = 0;
	nbr[1][0] = 0;
	nbr[1][1] = 1;
	nbr[1][2] = 0;
	nbr[1][3] = 0;
	nbr[2][0] = 0;
	nbr[2][1] = 0;
	nbr[2][2] = 1;
	nbr[2][3] = 0;
	while ((index += 3) < W_Y * rowstride - rowstride)
	{
		col[0] = (t[index + 0] + t[index + 3] + t[index + rowstride]) / 3;
		col[1] = (t[index + 1] + t[index + 4] + t[index + rowstride]) / 3;
		col[2] = (t[index + 2] + t[index + 5] + t[index + rowstride]) / 3;
		t[index + 0] = change_col(col, nbr[0]);
		t[index + 1] = change_col(col, nbr[1]);
		t[index + 2] = change_col(col, nbr[2]);
	}
}

void			brightness(unsigned char *t, int rowstride, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 1.5;
	nbr[0][1] = 0;
	nbr[0][2] = 0;
	nbr[0][3] = 0;
	nbr[1][0] = 0;
	nbr[1][1] = 1.5;
	nbr[1][2] = 0;
	nbr[1][3] = 0;
	nbr[2][0] = 0;
	nbr[2][1] = 0;
	nbr[2][2] = 1.5;
	nbr[2][3] = 0;
	while ((index += 3) < W_Y * rowstride)
	{
		col[0] = t[index + 0];
		col[1] = t[index + 1];
		col[2] = t[index + 2];
		t[index + 0] = change_col(col, nbr[0]);
		t[index + 1] = change_col(col, nbr[1]);
		t[index + 2] = change_col(col, nbr[2]);
	}
}

void			darkness(unsigned char *t, int rowstride, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 0.5;
	nbr[0][1] = 0;
	nbr[0][2] = 0;
	nbr[0][3] = 0;
	nbr[1][0] = 0;
	nbr[1][1] = 0.5;
	nbr[1][2] = 0;
	nbr[1][3] = 0;
	nbr[2][0] = 0;
	nbr[2][1] = 0;
	nbr[2][2] = 0.5;
	nbr[2][3] = 0;
	while ((index += 3) < W_Y * rowstride)
	{
		col[0] = t[index + 0];
		col[1] = t[index + 1];
		col[2] = t[index + 2];
		t[index + 0] = change_col(col, nbr[0]);
		t[index + 1] = change_col(col, nbr[1]);
		t[index + 2] = change_col(col, nbr[2]);
	}
}

void			negative(unsigned char *t, int rowstride, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 0;
	nbr[0][1] = 1;
	nbr[0][2] = 1;
	nbr[0][3] = 0;
	nbr[1][0] = 1;
	nbr[1][1] = 0;
	nbr[1][2] = 1;
	nbr[1][3] = 0;
	nbr[2][0] = 1;
	nbr[2][1] = 1;
	nbr[2][2] = 0;
	nbr[2][3] = 0;
	while ((index += 3) < W_Y * rowstride)
	{
		col[0] = t[index + 0];
		col[1] = t[index + 1];
		col[2] = t[index + 2];
		t[index + 0] = change_col(col, nbr[0]);
		t[index + 1] = change_col(col, nbr[1]);
		t[index + 2] = change_col(col, nbr[2]);
	}
}
