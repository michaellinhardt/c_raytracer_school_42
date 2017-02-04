/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 18:44:31 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_ARROW_LEFT];
	img->pos[0] = m->scene_img[1][IB_ARROW_LEFT_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_ARROW_LEFT_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_btn_left);
	set_over_click(m, img, IB_ARROW_LEFT_OVER, IB_ARROW_LEFT_CLICK);
	img = &m->scene_img[1][IB_ARROW_RIGHT_OFF];
	img->pos[0] = m->winx - img->width - 8;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_ARROW_RIGHT];
	img->pos[0] = m->scene_img[1][IB_ARROW_RIGHT_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_ARROW_RIGHT_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_btn_right);
	set_over_click(m, img, IB_ARROW_RIGHT_OVER, IB_ARROW_RIGHT_CLICK);
}

static void		part3(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_SPOT];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0]
	+ (2 * img->width) + (2 * BOT_BTN_X_DECALLAGE);
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_spot_btn_open);
	set_over_click(m, img, IB_SPOT_OVER, IB_SPOT_CLICK);
	img = &m->scene_img[1][IB_CAMERA];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0]
	+ (3 * img->width) + (3 * BOT_BTN_X_DECALLAGE);
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_camera_btn_open);
	set_over_click(m, img, IB_CAMERA_OVER, IB_CAMERA_CLICK);
	img = &m->scene_img[1][IB_ARROW_LEFT_OFF];
	img->pos[0] = 8;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
}

static void		part2(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IB_SAVE];
	img->pos[0] = m->scene_img[1][IB_SAVE_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_SAVE_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_save_btn_open);
	set_over_click(m, img, IB_SAVE_OVER, IB_SAVE_CLICK);
	img = &m->scene_img[1][IB_SCENE];
	img->pos[0] = 677;
	img->pos[1] = 960;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_btn_open);
	set_over_click(m, img, IB_SCENE_OVER, IB_SCENE_CLICK);
	img = &m->scene_img[1][IB_OBJECT];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0]
	+ (img->width) + (BOT_BTN_X_DECALLAGE);
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_object_btn_open);
	set_over_click(m, img, IB_OBJECT_OVER, IB_OBJECT_CLICK);
}

static void		part1(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][IMENU_CADRE_LOGO];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = 22;
	img->fade_min = 100;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IB_LOAD];
	img->pos[0] = 530;
	img->pos[1] = 11;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_load_btn_open);
	set_over_click(m, img, IB_LOAD_OVER, IB_LOAD_CLICK);
	img = &m->scene_img[1][IB_SAVE_OFF];
	img->pos[0] = 1095;
	img->pos[1] = m->scene_img[1][IB_LOAD].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
}

void			scene_init_1_rt_img_1(t_mlx *m, t_img *img)
{
	img = &m->getcursor;
	img->width = 2;
	img->heigh = INPUT_SIZE_CHAR_Y - INPUT_PADDING;
	img->img = mlx_new_img(m, img, img->width, img->heigh);
	img->i = -1;
	while (++img->i < img->width * img->heigh)
		img->ptr[img->i] = INPUT_CURSOR_COLOR;
	img->fade_min = 1;
	img->fade_max = 255;
	img = &m->scene_img[1][IMENU_CADRE];
	img->fade_min = 110;
	img->set_alpha = 0xFF000000;
	set_type_action(img, MENU, 0, NULL);
	img = &m->scene_img[1][IMENU_CADRE_LIGHTNING];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = 4;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);
	part1(m, img);
	part2(m, img);
	part3(m, img);
	part4(m, img);
}
