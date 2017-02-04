/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_debug_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:14:09 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:08 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int		abss(int i)
{
	return ((i < 0) ? i * -1 : i);
}

void	pixeltoimg(t_data *d, t_img *i, int x, int y)
{
	i->i = y * i->sl + x * 4;
	i->str[i->i] = ((d->map.color) ? 0 : 255);
	i->str[i->i + 1] = 255;
	i->str[i->i + 2] = 255;
	i->str[i->i + 3] = 0;
}

void	line(int x1, int y1, int x2, int y2)
{
	static t_data	*d = NULL;
	t_line			l;

	(!d) ? d = data() : (t_data *)NULL;
	l.dx = abss(x2 - x1);
	l.sx = x1 < x2 ? 1 : -1;
	l.dy = abss(y2 - y1);
	l.sy = y1 < y2 ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (42)
	{
		if (x1 < WIN_X && x1 > -1 && y1 < WIN_Y && y1 > -1)
			pixeltoimg(d, &d->fdf, x1, y1);
		if (x1 == x2 && y1 == y2)
			break ;
		l.e2 = l.err;
		if (l.e2 > -l.dx && ((l.err -= l.dy) || 1))
			x1 += l.sx;
		if (l.e2 < l.dy && ((l.err += l.dx) || 1))
			y1 += l.sy;
	}
}
