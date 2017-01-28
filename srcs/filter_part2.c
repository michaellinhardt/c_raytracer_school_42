/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 17:13:16 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/06 17:13:19 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void	sepia(char *data, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 0.393;
	nbr[0][1] = 0.769;
	nbr[0][2] = 0.189;
	nbr[0][3] = 0;
	nbr[1][0] = 0.349;
	nbr[1][1] = 0.686;
	nbr[1][2] = 0.168;
	nbr[1][3] = 0;
	nbr[2][0] = 0.272;
	nbr[2][1] = 0.534;
	nbr[2][2] = 0.131;
	nbr[2][3] = 0;
	while ((index += 4) < W_Y * W_X * 4)
	{
		col[0] = data[index + 2];
		col[1] = data[index + 1];
		col[2] = data[index + 0];
		data[index + 2] = change_col(col, nbr[0]);
		data[index + 1] = change_col(col, nbr[1]);
		data[index + 0] = change_col(col, nbr[2]);
	}
}

void	technicolor(char *data, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 1.913;
	nbr[0][1] = -0.855;
	nbr[0][2] = -0.092;
	nbr[0][3] = 11.794;
	nbr[1][0] = -0.309;
	nbr[1][1] = 1.766;
	nbr[1][2] = -0.106;
	nbr[1][3] = -70.352;
	nbr[2][0] = -0.231;
	nbr[2][1] = -0.75;
	nbr[2][2] = 1.848;
	nbr[2][3] = 30.951;
	while ((index += 4) < W_Y * W_X * 4)
	{
		col[0] = data[index + 2];
		col[1] = data[index + 1];
		col[2] = data[index + 0];
		data[index + 2] = change_col(col, nbr[0]);
		data[index + 1] = change_col(col, nbr[1]);
		data[index + 0] = change_col(col, nbr[2]);
	}
}

void	polaroid(char *data, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 1.438;
	nbr[0][1] = -0.062;
	nbr[0][2] = -0.062;
	nbr[0][3] = 0;
	nbr[1][0] = -0.122;
	nbr[1][1] = 1.378;
	nbr[1][2] = -0.122;
	nbr[1][3] = 0;
	nbr[2][0] = -0.016;
	nbr[2][1] = -0.016;
	nbr[2][2] = 1.483;
	nbr[2][3] = 0;
	while ((index += 4) < W_Y * W_X * 4)
	{
		col[0] = data[index + 2];
		col[1] = data[index + 1];
		col[2] = data[index + 0];
		data[index + 2] = change_col(col, nbr[0]);
		data[index + 1] = change_col(col, nbr[1]);
		data[index + 0] = change_col(col, nbr[2]);
	}
}

void	bgr(char *data, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 0;
	nbr[0][1] = 0;
	nbr[0][2] = 1;
	nbr[0][3] = 0;
	nbr[1][0] = 0;
	nbr[1][1] = 1;
	nbr[1][2] = 0;
	nbr[1][3] = 0;
	nbr[2][0] = 1;
	nbr[2][1] = 0;
	nbr[2][2] = 0;
	nbr[2][3] = 0;
	while ((index += 4) < W_Y * W_X * 4)
	{
		col[0] = data[index + 2];
		col[1] = data[index + 1];
		col[2] = data[index + 0];
		data[index + 2] = change_col(col, nbr[0]);
		data[index + 1] = change_col(col, nbr[1]);
		data[index + 0] = change_col(col, nbr[2]);
	}
}

void	kodachrome(char *data, int index)
{
	unsigned char	col[3];
	double			nbr[3][4];

	nbr[0][0] = 1.129;
	nbr[0][1] = -0.398;
	nbr[0][2] = -0.04;
	nbr[0][3] = 63.73;
	nbr[1][0] = -0.164;
	nbr[1][1] = 1.084;
	nbr[1][2] = -0.055;
	nbr[1][3] = 24.73;
	nbr[2][0] = -0.168;
	nbr[2][1] = -0.56;
	nbr[2][2] = 1.601;
	nbr[2][3] = 35.63;
	while ((index += 4) < W_Y * W_X * 4)
	{
		col[0] = data[index + 2];
		col[1] = data[index + 1];
		col[2] = data[index + 0];
		data[index + 2] = change_col(col, nbr[0]);
		data[index + 1] = change_col(col, nbr[1]);
		data[index + 0] = change_col(col, nbr[2]);
	}
}
