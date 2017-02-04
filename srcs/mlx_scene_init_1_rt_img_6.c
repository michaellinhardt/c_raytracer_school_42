/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_6.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:46:23 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_FILTER_CANCEL];
	img->pos[0] = m->scene_img[1][IMENU_FILTER_BOX].pos[0]
	+ m->scene_img[1][IMENU_FILTER_BOX].width - img->width * 1 - 5;
	img->pos[1] = m->scene_img[1][IMENU_FILTER_BOX].pos[1]
	+ m->scene_img[1][IMENU_FILTER_BOX].heigh - img->heigh - 20;
	img->menu = LOAD_FILTER;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_filter_btn_cancel);
	set_over_click(m, img, IB_FILTER_CANCEL_OVER, IB_FILTER_CANCEL_CLICK);
}

static void		part3(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_FILTER_OK];
	img->pos[0] = m->scene_img[1][IMENU_FILTER_BOX].pos[0]
	+ m->scene_img[1][IMENU_FILTER_BOX].width - img->width * 2 - 5;
	img->pos[1] = m->scene_img[1][IMENU_FILTER_BOX].pos[1]
	+ m->scene_img[1][IMENU_FILTER_BOX].heigh - img->heigh - 17;
	img->menu = LOAD_FILTER;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_filter_btn_ok);
	set_over_click(m, img, IB_FILTER_OK_OVER, IB_FILTER_OK_CLICK);
}

static void		part2(t_mlx *m, t_img *img, int i)
{
	while (++i < 15)
	{
		img = &m->scene_img[1][IB_FILTER1_OFF + i - 1];
		scene_img_copy(m, &m->scene_img[1][IB_CHECKBOX_NO], img);
		img->pos[0] = m->scene_img[1][IB_CHECKBOX_NO].pos[0]
		+ (((i - 1) % 2) * (m->scene_img[1][IMENU_FILTER_BOX].width / 2));
		img->pos[1] = m->scene_img[1][IB_CHECKBOX_NO].pos[1] + ((i - 1) / 2)
		* (img->heigh + 40);
		img->menu = LOAD_FILTER;
		set_area(img);
		set_type_action(img, MENU, 1, &menu_filter_checkbox_btn);
		img = &m->scene_img[1][IB_FILTER1_ON + i - 1];
		scene_img_copy(m, &m->scene_img[1][IB_CHECKBOX_YES], img);
		img->pos[0] = m->scene_img[1][IB_FILTER1_OFF + i - 1].pos[0];
		img->pos[1] = m->scene_img[1][IB_FILTER1_OFF + i - 1].pos[1];
		img->menu = LOAD_FILTER;
		set_area(img);
		set_type_action(img, DISABLED, 1, &menu_filter_checkbox_btn);
	}
}

static void		part1(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_CHECKBOX_YES];
	img->pos[0] = m->scene_img[1][IB_CHECKBOX_NO].pos[0];
	img->pos[1] = m->scene_img[1][IB_CHECKBOX_NO].pos[1];
	img->menu = LOAD_FILTER;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_filter_checkbox_btn);
}

void			scene_init_1_rt_img_6(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IMENU_FILTER_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_FILTER;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_CHECKBOX_NO];
	img->pos[0] = m->scene_img[1][IMENU_FILTER_BOX].pos[0] + 25;
	img->pos[1] = m->scene_img[1][IMENU_FILTER_BOX].pos[1] + 25;
	img->menu = LOAD_FILTER;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_filter_checkbox_btn);
	part1(m, img);
	part2(m, img, 0);
	part3(m, img);
	part4(m, img);
}
