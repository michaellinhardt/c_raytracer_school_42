/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:09 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:10 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		menu_draw_actif_sub(t_mlx *m, t_img *img)
{
	if (m->menu.id == LOAD_SCENE_ADD || m->menu.id == LOAD_OBJECT_ADD
	|| m->menu.id == LOAD_SPOT_ADD)
		img = &m->scene_img[1][IB_E_ADD];
	else if (m->menu.id == LOAD_SCENE || m->menu.id == LOAD_OBJECT
	|| m->menu.id == LOAD_SPOT)
		img = &m->scene_img[1][IB_E_SWITCH];
	else if (m->menu.id == LOAD_SCENE_EDIT || m->menu.id == LOAD_OBJECT_EDIT
	|| m->menu.id == LOAD_SPOT_EDIT)
		img = &m->scene_img[1][IB_E_MOD];
	else if (m->menu.id == LOAD_SCENE_DEL || m->menu.id == LOAD_OBJECT_DEL
	|| m->menu.id == LOAD_SPOT_DEL)
		img = &m->scene_img[1][IB_E_DEL];
	else
		return ;
	m->scene_img[1][IB_SELECTED].pos[0] = img->pos[0] - 3;
	m->scene_img[1][IB_SELECTED].pos[1] = img->pos[1] - 3;
	img = &m->scene_img[1][IB_SELECTED];
	layer_add(m, layer(m, 1, 0), img);
}

void			menu_draw_actif(t_mlx *m, t_img *img)
{
	if (m->menu.draw == -1 || m->menu.loading != 0)
		return ;
	else if (m->menu.id == LOAD_FILE)
		img = &m->scene_img[1][IB_LOAD];
	else if (m->menu.id >= LOAD_SCENE && m->menu.id < LOAD_OBJECT)
		img = &m->scene_img[1][IB_SCENE];
	else if (m->menu.id >= LOAD_OBJECT && m->menu.id < LOAD_SPOT)
		img = &m->scene_img[1][IB_OBJECT];
	else if (m->menu.id >= LOAD_SPOT && m->menu.id < LOAD_CAMERA)
		img = &m->scene_img[1][IB_SPOT];
	else if (m->menu.id == LOAD_CAMERA)
		img = &m->scene_img[1][IB_CAMERA];
	else if (m->menu.id == LOAD_FILTER)
		img = &m->scene_img[1][IB_FILTER];
	m->scene_img[1][IB_SELECTED].pos[0] = img->pos[0] - 3;
	m->scene_img[1][IB_SELECTED].pos[1] = img->pos[1] - 3;
	img = &m->scene_img[1][IB_SELECTED];
	layer_add(m, layer(m, 1, 0), img);
	menu_draw_actif_sub(m, (t_img *)NULL);
}

void			scene_build(t_gen *d, t_mlx *m, t_img *lay, t_img *img)
{
	int		i;

	i = -1;
	if (m->menu.draw == 1)
		layer(m, 1, 1);
	if (m->scene == RT && m->menu.draw == 1
	&& m->menu.id >= LOAD_FILE && m->menu.id < LOAD_CAMERA)
		menu_draw(m, m->flst, -1, -1);
	while (m->scene_img[m->scene][++i].img)
	{
		if (((img = &m->scene_img[m->scene][i])->status > MENU)
		|| (m->menu.draw == 1 && img->status == MENU
		&& (img->menu == NONE || img->menu == m->menu.id)))
			layer_add(m, lay, img);
	}
	menu_draw_actif(m, (t_img *)NULL);
	(void)d;
}
