/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:37:06 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_E_MOD];
	img->pos[0] = m->scene_img[1][IB_E_MOD_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_MOD_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_mod_btn_open);
	set_over_click(m, img, IB_E_MOD_OVER, IB_E_MOD_CLICK);
	img = &m->scene_img[1][IB_E_ADD_OFF];
	img->pos[0] = m->scene_img[1][IB_GEN_DATA_OFF].pos[0]
	+ (img->width * 3) + (BOT_BTN_X_DECALLAGE * 3);
	img->pos[1] = m->scene_img[1][IB_GEN_DATA_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_E_ADD];
	img->pos[0] = m->scene_img[1][IB_E_ADD_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_ADD_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_add_btn_open);
	set_over_click(m, img, IB_E_ADD_OVER, IB_E_ADD_CLICK);
}

static void		part3(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_GEN_BMP_OFF];
	img->pos[0] = m->scene_img[1][IB_GEN_DATA_OFF].pos[0]
	+ (img->width * 1) + (BOT_BTN_X_DECALLAGE * 1);
	img->pos[1] = m->scene_img[1][IB_GEN_DATA_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_GEN_BMP];
	img->pos[0] = m->scene_img[1][IB_GEN_BMP_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_GEN_BMP_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_gen_bmp_btn);
	set_over_click(m, img, IB_GEN_BMP_OVER, IB_GEN_BMP_CLICK);
	img = &m->scene_img[1][IB_E_MOD_OFF];
	img->pos[0] = m->scene_img[1][IB_GEN_DATA_OFF].pos[0]
	+ (img->width * 2) + (BOT_BTN_X_DECALLAGE * 2);
	img->pos[1] = m->scene_img[1][IB_GEN_DATA_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
}

static void		part2(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_CAMERA_OFF];
	img->pos[0] = m->scene_img[1][IB_CAMERA].pos[0];
	img->pos[1] = m->scene_img[1][IB_CAMERA].pos[1];
	img->fade_min = m->scene_img[1][IB_CAMERA].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_GEN_DATA_OFF];
	img->pos[0] = 50;
	img->pos[1] = 952;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_GEN_DATA];
	img->pos[0] = m->scene_img[1][IB_GEN_DATA_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_GEN_DATA_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_gen_data_btn);
	set_over_click(m, img, IB_GEN_DATA_OVER, IB_GEN_DATA_CLICK);
}

static void		part1(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_SCENE_OFF];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0];
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = m->scene_img[1][IB_SCENE].fade_min;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 0, NULL);
	img = &m->scene_img[1][IB_OBJECT_OFF];
	img->pos[0] = m->scene_img[1][IB_OBJECT].pos[0];
	img->pos[1] = m->scene_img[1][IB_OBJECT].pos[1];
	img->fade_min = m->scene_img[1][IB_OBJECT].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_SPOT_OFF];
	img->pos[0] = m->scene_img[1][IB_SPOT].pos[0];
	img->pos[1] = m->scene_img[1][IB_SPOT].pos[1];
	img->fade_min = m->scene_img[1][IB_SPOT].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
}

void			scene_init_1_rt_img_2(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IMG_PREVIEW_NO_IMG];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);
	img = &m->scene_img[1][IMG_PREVIEW];
	img->fade_min = 100;
	img->set_alpha = -1;
	layer_set_alpha(img);
	img = &m->scene_img[1][IMG_PREVIEW_OVER];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);
	img = &m->scene_img[1][IMG_PREVIEW_CLIC];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);
	part1(m, img);
	part2(m, img);
	part3(m, img);
	part4(m, img);
}
