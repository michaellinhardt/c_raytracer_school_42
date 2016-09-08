/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 17:12:59 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/06 17:13:02 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

unsigned char	change_col(unsigned char *col, double *nbr)
{
	unsigned char index;

	if (col[0] * nbr[0] + col[1] * nbr[1] + col[2] * nbr[2] + nbr[3] > 0)
	{
		index = ((col[0] * nbr[0] + col[1] * nbr[1] + col[2] * nbr[2] +
		nbr[3] > 0xff)) ? (unsigned char)0xff : (unsigned char)((col[0] * nbr[0]
		+ col[1] * nbr[1] + col[2] * nbr[2] + nbr[3]));
		return (index);
	}
	return (0);
}
//mettre index a -3; rowstride = gdk_pixbuf_get_rowstride(pixbuf);

void	abstract(unsigned char *t, int rowstride, int index)
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

void	brightness(unsigned char *t, int rowstride, int index)
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

void	darkness(unsigned char *t, int rowstride, int index)
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

void	negative(unsigned char *t, int rowstride, int index)
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