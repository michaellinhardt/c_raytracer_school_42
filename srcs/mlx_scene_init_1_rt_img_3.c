/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 18:45:02 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_SCENE_DEL_CANCEL];
	img->pos[0] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].width - img->width * 1 - 5;
	img->pos[1] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].heigh - img->heigh - 20;
	img->menu = LOAD_SCENE_DEL;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_del_btn_cancel);
	set_over_click(m, img, IB_SCENE_DEL_CANCEL_OVER, IB_SCENE_DEL_CANCEL_CLICK);
	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	img->pos[0] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[0] + 360;
	img->pos[1] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[1]
	+ m->scene_img[1][IMENU_EDIT_OBJECT_BOX].heigh - 80 - img->heigh * 2;
	set_type_action(img, DISABLED, 8, NULL);
	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 8, NULL);
}

static void		part3(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IMENU_EDIT_SCENE_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SCENE_EDIT;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SCENE_DEL;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_SCENE_DEL_OK];
	img->pos[0] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].width - img->width * 2 - 5;
	img->pos[1] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].heigh - img->heigh - 17;
	img->menu = LOAD_SCENE_DEL;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_del_btn_ok);
	set_over_click(m, img, IB_SCENE_DEL_OK_OVER, IB_SCENE_DEL_OK_CLICK);
}

static void		part2(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IMENU_ADD_SCENE_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SCENE_ADD;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_SCENE_ADD_OK];
	img->pos[0] = m->scene_img[1][IMENU_ADD_SCENE_BOX].pos[0]
	+ m->scene_img[1][IMENU_ADD_SCENE_BOX].width - img->width - 5;
	img->pos[1] = m->scene_img[1][IMENU_ADD_SCENE_BOX].pos[1]
	+ m->scene_img[1][IMENU_ADD_SCENE_BOX].heigh - img->heigh - 5;
	img->menu = LOAD_SCENE_ADD;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_add_btn_ok);
	set_over_click(m, img, IB_SCENE_ADD_OK_OVER, IB_SCENE_ADD_OK_CLICK);
	img = &m->scene_img[1][IMENU_EDIT_OBJECT_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
}

static void		part1(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_E_DEL_OFF];
	img->pos[0] = m->scene_img[1][IB_GEN_DATA_OFF].pos[0]
	+ (5 * img->width) + (5 * BOT_BTN_X_DECALLAGE);
	img->pos[1] = m->scene_img[1][IB_GEN_DATA_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_E_DEL];
	img->pos[0] = m->scene_img[1][IB_E_DEL_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_DEL_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_del_btn_open);
	set_over_click(m, img, IB_E_DEL_OVER, IB_E_DEL_CLICK);
	img = &m->scene_img[1][IB_SELECTED];
	img->fade_min = 100;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 0, NULL);
}

void			scene_init_1_rt_img_3(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_E_SWITCH_OFF];
	img->pos[0] = m->scene_img[1][IB_GEN_DATA_OFF].pos[0]
	+ (img->width * 4) + (BOT_BTN_X_DECALLAGE * 4);
	img->pos[1] = m->scene_img[1][IB_GEN_DATA_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_E_SWITCH];
	img->pos[0] = m->scene_img[1][IB_E_SWITCH_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_SWITCH_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_switch_btn_open);
	set_over_click(m, img, IB_E_SWITCH_OVER, IB_E_SWITCH_CLICK);
	part1(m, img);
	part2(m, img);
	part3(m, img);
	part4(m, img);
}
