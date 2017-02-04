/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_5.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:43:44 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_SPOT_ADD_OK];
	set_type_action(img, MENU, 1, &menu_spot_add_btn_ok);
	set_over_click(m, img, IB_SPOT_ADD_OK_OVER, IB_SPOT_ADD_OK_CLICK);
	img = &m->scene_img[1][IMENU_EDIT_CAMERA_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_CAMERA;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_FILTER_OFF];
	img->pos[0] = 30;
	img->pos[1] = W_Y - (img->width * 2) - 25;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_FILTER];
	img->pos[0] = m->scene_img[1][IB_FILTER_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_FILTER_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_filter_btn_open);
	set_over_click(m, img, IB_FILTER_OVER, IB_FILTER_CLICK);
}

static void		part3(t_mlx *m, t_img *img, int i)
{
	while (++i < 3)
	{
		img = &m->scene_img[1][IB_SPOT_MOD_TYPE_SELECT2 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = m->scene_img[1][IB_SPOT_MOD_TYPE_SELECT2 + i - 2].pos[0];
		img->pos[1] = m->scene_img[1][IB_SPOT_MOD_TYPE_SELECT2 + i - 2].pos[1];
		set_area(img);
		set_type_action(img, MENU, 1, &menu_spot_mod_btn_type);
		set_over_click(m, img, (IB_SPOT_MOD_TYPE_SELECT2 + i) - 4
		, (IB_SPOT_MOD_TYPE_SELECT2 + i) - 2);
	}
	img = &m->scene_img[1][IMENU_ADD_SPOT_BOX];
	scene_img_copy(m, &m->scene_img[1][IMENU_ADD_SCENE_BOX], img);
	img->menu = LOAD_SPOT_ADD;
	img = &m->scene_img[1][IB_SPOT_ADD_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK], img);
	img->menu = LOAD_SPOT_ADD;
	img = &m->scene_img[1][IB_SPOT_ADD_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_OVER], img);
	img->menu = LOAD_SPOT_ADD;
	img = &m->scene_img[1][IB_SPOT_ADD_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_CLICK], img);
	img->menu = LOAD_SPOT_ADD;
}

static void		part2(t_mlx *m, t_img *img, int i)
{
	while (++i < 3)
	{
		img = &m->scene_img[1][IB_SPOT_MOD_TYPE_OFF2 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = m->scene_img[1][IB_SPOT_MOD_TYPE_OFF2 + i - 2].pos[0];
		img->pos[1] = m->scene_img[1][IB_SPOT_MOD_TYPE_OFF2 + i - 2].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}
	i = 0;
	while (++i < 3)
	{
		img = &m->scene_img[1][IB_SPOT_MOD_TYPE_OVER2 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = m->scene_img[1][IB_SPOT_MOD_TYPE_OVER2 + i - 2].pos[0];
		img->pos[1] = m->scene_img[1][IB_SPOT_MOD_TYPE_OVER2 + i - 2].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}
}

static void		part1(t_mlx *m, t_img *img, int i)
{
	img = &m->scene_img[1][IB_SPOT_DEL_CANCEL];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL], img);
	img->menu = LOAD_SPOT_DEL;
	set_type_action(img, MENU, 1, &menu_spot_del_btn_cancel);
	set_over_click(m, img, IB_SPOT_DEL_CANCEL_OVER, IB_SPOT_DEL_CANCEL_CLICK);
	img = &m->scene_img[1][IMENU_EDIT_SPOT_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SPOT_EDIT;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	while (++i < 3)
	{
		img = &m->scene_img[1][IMENU_EDIT_SPOT_BOX + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = 50 + m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[0]
		+ (i * 200);
		img->pos[1] = m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[1]
		+ m->scene_img[1][IMENU_EDIT_SPOT_BOX].heigh - 100;
		set_area(img);
		set_type_action(img, MENU, 8, NULL);
	}
}

void			scene_init_1_rt_img_5(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_SPOT_DEL_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_CLICK], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK], img);
	img->menu = LOAD_SPOT_DEL;
	set_type_action(img, MENU, 1, &menu_spot_del_btn_ok);
	set_over_click(m, img, IB_SPOT_DEL_OK_OVER, IB_SPOT_DEL_OK_CLICK);
	img = &m->scene_img[1][IB_SPOT_DEL_CANCEL_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_OVER], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_CANCEL_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_CLICK], img);
	img->menu = LOAD_SPOT_DEL;
	part1(m, img, 0);
	part2(m, img, 0);
	part3(m, img, 0);
	part4(m, img);
}
