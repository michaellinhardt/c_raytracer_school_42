/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_check_area.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:05 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:06 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

int			area(t_img *img, t_flst *elem, int x, int y)
{
	int		topx;
	int		topy;
	int		botx;
	int		boty;

	topx = (img) ? img->mouse.top[0] : elem->top[0];
	topy = (img) ? img->mouse.top[1] : elem->top[1];
	botx = (img) ? img->mouse.bot[0] : elem->bot[0];
	boty = (img) ? img->mouse.bot[1] : elem->bot[1];
	if (x >= topx && x <= botx && y >= topy && y <= boty)
		return (1);
	return (0);
}
