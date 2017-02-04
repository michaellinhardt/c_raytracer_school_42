/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_0.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 18:38:18 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

void				scene_init_1_rt_input_area(t_mlx *m, t_get *g, int i)
{
	while (++i < GET_APP_MAX)
	{
		if (!(g = &m->get[i])->menu)
			continue ;
		g->box.mouse.top[0] = g->box.pos[0];
		g->box.mouse.top[1] = g->box.pos[1];
		g->box.width = INPUT_SIZE_CHAR_X * g->size_max + INPUT_PADDING;
		g->box.heigh = INPUT_SIZE_CHAR_Y + INPUT_PADDING;
		g->box.mouse.bot[0] = g->box.pos[0] + g->box.width;
		g->box.mouse.bot[1] = g->box.pos[1] + g->box.heigh;
	}
}

void				scene_img_copy(t_mlx *m, t_img *src, t_img *dst)
{
	dst->width = src->width;
	dst->heigh = src->heigh;
	dst->fade_min = src->fade_min;
	dst->fade_max = src->fade_max;
	dst->set_alpha = src->set_alpha;
	dst->menu = src->menu;
	dst->pos[0] = src->pos[0];
	dst->pos[1] = src->pos[1];
	set_type_action(dst, src->status, src->mouse.btn, src->mouse.action);
	if (!dst->img)
		dst->img = mlx_new_img(m, dst, src->width, src->heigh);
	dst->i = -1;
	while (++dst->i < dst->width * dst->heigh)
		dst->ptr[dst->i] = src->ptr[dst->i];
	set_area(dst);
}

void				scene_init_1_rt_input(t_gen *d, t_mlx *m, t_get *g)
{
	scene_init_1_rt_get_1(m, g);
	scene_init_1_rt_get_2(m, g);
	scene_init_1_rt_get_3(m, g);
	(void)d;
}

void				scene_init_1_rt_img(t_gen *d, t_mlx *m, t_img *img)
{
	scene_init_1_rt_img_1(m, img);
	scene_init_1_rt_img_2(m, img);
	scene_init_1_rt_img_3(m, img);
	scene_init_1_rt_img_4(m, img);
	scene_init_1_rt_img_5(m, img);
	scene_init_1_rt_img_6(m, img);
	scene_init_1_rt_input(d, m, (t_get *)NULL);
	scene_init_1_rt_input_area(m, (t_get *)NULL, -1);
}
