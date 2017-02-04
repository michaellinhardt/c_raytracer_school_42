/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init_1_rt_img_0.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:15 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 16:48:26 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

void				scene_init_1_rt_input_area(t_mlx *m, t_get *g, int i)
{
	while (++i < GET_APP_MAX)
	{
		if (!(g = &m->get[i])->menu)
			continue ;
		g->box.mouse.top[0] = g->box.pos[0];
		g->box.mouse.top[1] = g->box.pos[1];
		g->box.width = INPUT_SIZE_CHAR_X * g->size_max + INPUT_PADDING;
		g->box.heigh = INPUT_SIZE_CHAR_Y + INPUT_PADDING;
		g->box.mouse.bot[0] = g->box.pos[0] + g->box.width;
		g->box.mouse.bot[1] = g->box.pos[1] + g->box.heigh;
	}
}

void				scene_img_copy(t_mlx *m, t_img *src, t_img *dst)
{
	dst->width = src->width;
	dst->heigh = src->heigh;
	dst->fade_min = src->fade_min;
	dst->fade_max = src->fade_max;
	dst->set_alpha = src->set_alpha;
	dst->menu = src->menu;
	dst->pos[0] = src->pos[0];
	dst->pos[1] = src->pos[1];
	set_type_action(dst, src->status, src->mouse.btn, src->mouse.action);
	if (!dst->img)
		dst->img = mlx_new_img(m, dst, src->width, src->heigh);
	dst->i = -1;
	while (++dst->i < dst->width * dst->heigh)
		dst->ptr[dst->i] = src->ptr[dst->i];
	set_area(dst);
}

void			scene_init_1_rt_input(t_gen *d, t_mlx *m, t_get *g)
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
	(void)d;
}

void			scene_init_1_rt_img(t_gen *d, t_mlx *m, t_img *img)
{
	scene_init_1_rt_img_1(m, img);
	scene_init_1_rt_img_2(m, img);
	scene_init_1_rt_img_3(m, img);
	scene_init_1_rt_img_4(m, img);
	scene_init_1_rt_img_5(m, img);
	scene_init_1_rt_img_6(m, img);

	scene_init_1_rt_input(d, m, (t_get *)NULL);
	scene_init_1_rt_input_area(m, (t_get *)NULL, -1);
}
