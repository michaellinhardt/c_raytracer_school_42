/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_4.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 17:27:35 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_OBJECT_DEL_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK], img);
	img->menu = LOAD_OBJECT_DEL;
	set_type_action(img, MENU, 1, &menu_object_del_btn_ok);
	set_over_click(m, img, IB_OBJECT_DEL_OK_OVER, IB_OBJECT_DEL_OK_CLICK);
	img = &m->scene_img[1][IB_OBJECT_DEL_CANCEL_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_OVER], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_CANCEL_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_CLICK], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_CANCEL];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL], img);
	img->menu = LOAD_OBJECT_DEL;
	set_type_action(img, MENU, 1, &menu_object_del_btn_cancel);
	set_over_click(m, img, IB_OBJECT_DEL_CANCEL_OVER
		, IB_OBJECT_DEL_CANCEL_CLICK);
	img = &m->scene_img[1][IMENU_EDIT_SPOT_BOX_DEL];
	scene_img_copy(m, &m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_OVER], img);
	img->menu = LOAD_SPOT_DEL;
}

static void		part3(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_OBJECT_ADD_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK], img);
	img->menu = LOAD_OBJECT_ADD;
	img = &m->scene_img[1][IB_OBJECT_ADD_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_OVER], img);
	img->menu = LOAD_OBJECT_ADD;
	img = &m->scene_img[1][IB_OBJECT_ADD_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_CLICK], img);
	img->menu = LOAD_OBJECT_ADD;
	img = &m->scene_img[1][IB_OBJECT_ADD_OK];
	set_type_action(img, MENU, 1, &menu_object_add_btn_ok);
	set_over_click(m, img, IB_OBJECT_ADD_OK_OVER, IB_OBJECT_ADD_OK_CLICK);
	img = &m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL];
	scene_img_copy(m, &m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_OVER], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_CLICK], img);
	img->menu = LOAD_OBJECT_DEL;
}

static void		part2(t_mlx *m, t_img *img, int i)
{
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER9 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT], img);
		img->pos[0] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER9 + i - 9].pos[0];
		img->pos[1] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER9 + i - 9].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}
	i = 0;
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJEC_MOD_TYP_SELCT9 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE], img);
		img->pos[0] = m->scene_img[1][IB_OBJEC_MOD_TYP_SELCT9 + i - 9].pos[0];
		img->pos[1] = m->scene_img[1][IB_OBJEC_MOD_TYP_SELCT9 + i - 9].pos[1];
		set_area(img);
		set_type_action(img, MENU, 1, &menu_object_mod_btn_type);
		set_over_click(m, img, (IB_OBJEC_MOD_TYP_SELCT9 + i) - 18
		, (IB_OBJEC_MOD_TYP_SELCT9 + i) - 9);
	}
	img = &m->scene_img[1][IMENU_ADD_OBJECT_BOX];
	scene_img_copy(m, &m->scene_img[1][IMENU_ADD_SCENE_BOX], img);
	img->menu = LOAD_OBJECT_ADD;
}

static void		part1(t_mlx *m, t_img *img, int i)
{
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF], img);
		img->pos[0] += (i % 3 - 1) * 320;
		if (i > 3 && i < 7)
			img->pos[1] += (img->heigh + 10);
		else if (i > 6)
			img->pos[1] += (img->heigh + 10) * 2;
		set_area(img);
		set_type_action(img, MENU, 8, NULL);
	}
	i = 0;
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF9 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER], img);
		img->pos[0] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF9 + i - 9].pos[0];
		img->pos[1] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF9 + i - 9].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}
}

void			scene_init_1_rt_img_4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 8, NULL);
	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 8, NULL);
	part1(m, img, 0);
	part2(m, img, 0);
	part3(m, img);
	part4(m, img);
}
