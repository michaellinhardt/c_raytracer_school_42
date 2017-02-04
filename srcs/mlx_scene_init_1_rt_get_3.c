/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_get_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:57:47 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		part4(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_CAM5];
	g->menu = LOAD_CAMERA;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_CAM2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_CAM4].box.pos[1];
	g->name = ft_strdup(TXT_CAMERA_MOD_CAM5);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_CAM6];
	g->menu = LOAD_CAMERA;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_CAM3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_CAM4].box.pos[1];
	g->name = ft_strdup(TXT_CAMERA_MOD_CAM6);
	g->size_min = 1;
	g->size_max = 17;
}

static void		part3(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_CAM2];
	g->menu = LOAD_CAMERA;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_CAM1].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_CAM1].box.pos[1];
	g->name = ft_strdup(TXT_CAMERA_MOD_CAM2);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_CAM3];
	g->menu = LOAD_CAMERA;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_CAM2].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_CAM2].box.pos[1];
	g->name = ft_strdup(TXT_CAMERA_MOD_CAM3);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_CAM4];
	g->menu = LOAD_CAMERA;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_CAM1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_CAM1].box.pos[1] + 10
	+ m->get[ID_INPUT_CAM1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_CAMERA_MOD_CAM4);
	g->size_min = 3;
	g->size_max = 17;
}

static void		part2(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_ADD_SPOT_NAME];
	g->menu = LOAD_SPOT_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_spot = ft_strdup(TXT_SPOT_ADD_NAME_DEFAUT);
	g->name = ft_strdup(TXT_SPOT_ADD_NAME);
	g->target.ptr_str = &m->menu.new_spot;
	g->box.pos[0] = 541;
	g->box.pos[1] = 483;
	g->size_min = 3;
	g->size_max = 59;
	g = &m->get[ID_INPUT_CAM1];
	g->menu = LOAD_CAMERA;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_CAMERA_BOX].pos[0] + 18;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_CAMERA_BOX].pos[1] + 90;
	g->name = ft_strdup(TXT_CAMERA_MOD_CAM1);
	g->size_min = 3;
	g->size_max = 17;
}

static void		part1(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_SPOT_POS5];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS5);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_SPOT_POS6];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS6);
	g->size_min = 1;
	g->size_max = 17;
}

void			scene_init_1_rt_get_3(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_SPOT_POS3];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS2].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS2].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS3);
	g->size_min = 1;
	g->size_max = 17;
	g = &m->get[ID_INPUT_SPOT_POS4];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS1].box.pos[1] + 10
	+ m->get[ID_INPUT_SPOT_POS1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_SPOT_MOD_POS4);
	g->size_min = 3;
	g->size_max = 17;
	part1(m, img);
	part2(m, img);
	part3(m, img);
	part4(m, img);
}
