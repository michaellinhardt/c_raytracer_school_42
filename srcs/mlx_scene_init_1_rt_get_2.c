/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_get_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:56:20 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_SPOT_COLOR];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_HEXA;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_NAME].box.pos[0] + 710;
	g->box.pos[1] = m->get[ID_INPUT_SPOT_NAME].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_COLOR);
	g->size_min = 6;
	g->size_max = 7;
	g = &m->get[ID_INPUT_SPOT_POS1];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_NAME].box.pos[1] + 10
	+ m->get[ID_INPUT_SPOT_NAME].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_SPOT_MOD_POS1);
	g->size_min = 3;
	g->size_max = 17;
	g = &m->get[ID_INPUT_SPOT_POS2];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS1].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS1].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS2);
	g->size_min = 1;
	g->size_max = 17;
}

static void		part3(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_ADD_OBJECT_NAME];
	g->menu = LOAD_OBJECT_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_object = ft_strdup(TXT_OBJECT_ADD_NAME_DEFAUT);
	g->name = ft_strdup(TXT_OBJECT_ADD_NAME);
	g->target.ptr_str = &m->menu.new_object;
	g->box.pos[0] = 541;
	g->box.pos[1] = 483;
	g->size_min = 3;
	g->size_max = 59;
	g = &m->get[ID_INPUT_SPOT_NAME];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_STRING_FILE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[0] + 15;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[1] + 40;
	g->name = ft_strdup(TXT_SPOT_MOD_NAME);
	g->size_min = 3;
	g->size_max = 59;
}

static void		part2(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_OBJECT_EFF5];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF5);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_EFF6];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF6);
	g->size_min = 1;
	g->size_max = 17;
}

static void		part1(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_OBJECT_EFF2];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF2);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_EFF3];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF3);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_EFF4];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF1].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_POS1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF4);
	g->size_min = 3;
	g->size_max = 17;
}

void			scene_init_1_rt_get_2(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_OBJECT_SIZE3];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_SIZE1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_SIZE3);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_EFF1];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_SIZE3].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_NAME].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF1);
	g->size_min = 3;
	g->size_max = 17;
	part1(m, img);
	part2(m, img);
	part3(m, img);
	part4(m, img);
}
