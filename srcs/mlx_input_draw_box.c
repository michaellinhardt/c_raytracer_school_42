/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_input_draw_box.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:35 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:35 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		prepare_box(t_get *g, t_img *img)
{
	unsigned		color;

	color = INPUT_COLOR_DISABLED;
	if (g->status != GET_DISABLED)
		color = INPUT_COLOR_ENABLED;
	img->i = -1;
	while (++img->i < img->width * img->heigh)
		img->ptr[img->i] = color;
}

static void		prepare_border(t_get *g, t_img *img, int x, int y)
{
	unsigned		color;

	color = INPUT_BORDER_COLOR;
	if (g->status == GET_FOCUS)
		color = INPUT_BORDER_COLOR_FOCUS;
	while (++y < img->heigh)
	{
		x = -1;
		if (y < INPUT_BORDER_SIZE)
			while (++x < img->width)
				img->ptr[y * img->width + x] = color;
		else if (y >= INPUT_BORDER_SIZE && y < img->heigh - INPUT_BORDER_SIZE)
		{
			while (++x < INPUT_BORDER_SIZE)
				img->ptr[y * img->width + x] = color;
			x = img->width;
			while (--x >= img->width - INPUT_BORDER_SIZE)
				img->ptr[y * img->width + x] = color;
		}
		else if (y >= img->heigh - INPUT_BORDER_SIZE)
			while (++x < img->width)
				img->ptr[y * img->width + x] = color;
	}
}

void			scene_input_draw_box(t_gen *d, t_mlx *m, t_get *g, t_img *lay)
{
	if (!g->box.img)
	{
		g->box.img = mlx_new_img(m, &g->box, g->box.width, g->box.heigh);
		prepare_box(g, &g->box);
	}
	prepare_border(g, &g->box, -1, -1);
	layer_add(m, lay, &g->box);
	(void)d;
}
