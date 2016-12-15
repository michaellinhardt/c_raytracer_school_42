/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:20:29 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/11 01:13:16 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void		color_composants(int color, double *ret)
{
	int r;
	int g;
	int b;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	ret[0] = (double)r / 255.0;
	ret[1] = (double)g / 255.0;
	ret[2] = (double)b / 255.0;
}

int			colorfromrgb(double *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0] * 255;
	g = rgb[1] * 255;
	b = rgb[2] * 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

double		sqr(double color)
{
	return (color * color);
}

void		color_normalize(double *tab, double *tmp_tab, double factor, int c)
{
	if (c)
	{
		tab[0] = (tab[0] + sqr(tmp_tab[0]) * factor);
		tab[1] = (tab[1] + sqr(tmp_tab[1]) * factor);
		tab[2] = (tab[2] + sqr(tmp_tab[2]) * factor);
	}
	else
	{
		tab[0] = (tab[0] * tmp_tab[0]) * factor;
		tab[1] = (tab[1] * tmp_tab[1]) * factor;
		tab[2] = (tab[2] * tmp_tab[2]) * factor;
	}
}
