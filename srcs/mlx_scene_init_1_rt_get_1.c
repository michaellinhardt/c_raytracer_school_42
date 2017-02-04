/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_get_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 17:01:25 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_OBJECT_POS6];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS6);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_SIZE1];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS4].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_SIZE1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_SIZE1);
	g->size_min = 3;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_SIZE2];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_SIZE1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_SIZE2);
	g->size_min = 1;
	g->size_max = 17;
}

static void		part3(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_OBJECT_POS3];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS2].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS3);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_POS4];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS1].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_POS1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_POS4);
	g->size_min = 3;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_POS5];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS5);
	g->size_min = 1;
	g->size_max = 17;
}

static void		part2(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_OBJECT_COLOR];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_HEXA;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_NAME].box.pos[0] + 710;
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_NAME].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_COLOR);
	g->size_min = 6;
	g->size_max = 7;
	g = &m->get[ID_INPUT_OBJECT_POS1];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_NAME].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_NAME].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_POS1);
	g->size_min = 3;
	g->size_max = 17;
	g = &m->get[ID_INPUT_OBJECT_POS2];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS2);
	g->size_min = 1;
	g->size_max = 17;
}

static void		part1(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_SCENE_AMBIANCE1];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_HEXA_TO_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_MOD_SCENE_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_MOD_SCENE_NAME].box.pos[1]
	+ INPUT_SIZE_CHAR_Y * 2 + 15;
	g->name = ft_strdup(TXT_SCENE_MOD_AMB1);
	g->size_min = 6;
	g->size_max = 7;
	g = &m->get[ID_INPUT_SCENE_AMBIANCE2];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[0] + 347;
	g->box.pos[1] = m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[1];
	g->name = ft_strdup(TXT_SCENE_MOD_AMB2);
	g->size_min = 3;
	g->size_max = 25;
	g = &m->get[ID_INPUT_OBJECT_NAME];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_STRING_FILE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[0] + 15;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[1] + 40;
	g->name = ft_strdup(TXT_OBJECT_MOD_NAME);
	g->size_min = 3;
	g->size_max = 59;
}

void			scene_init_1_rt_get_1(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_ADD_SCENE_NAME];
	g->menu = LOAD_SCENE_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_scene = ft_strdup(TXT_SCENE_ADD_NAME_DEFAUT);
	g->name = ft_strdup(TXT_SCENE_ADD_NAME);
	g->target.ptr_str = &m->menu.new_scene;
	g->box.pos[0] = 541;
	g->box.pos[1] = 483;
	g->size_min = 3;
	g->size_max = 59;
	g = &m->get[ID_INPUT_MOD_SCENE_NAME];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_STRING_FILE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_SCENE_BOX].pos[0] + 15;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_SCENE_BOX].pos[1] + 40;
	g->name = ft_strdup(TXT_SCENE_MOD_NAME);
	g->size_min = 3;
	g->size_max = 59;
	part1(m, g);
	part2(m, g);
	part3(m, g);
	part4(m, g);
}
