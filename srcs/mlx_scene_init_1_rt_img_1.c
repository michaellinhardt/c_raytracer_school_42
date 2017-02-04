/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:32:11 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part1(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;
}

static void		part2(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;
}

static void		part3(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;
}

static void		part4(t_mlx *m, t_img *img)
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
