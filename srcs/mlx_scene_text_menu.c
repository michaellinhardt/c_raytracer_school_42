#include "raystruct.h"

static void		scene_text_object_mod(t_mlx *m, int c, char msg[512])
{
	mlx_string_put(m->mlx, m->win, m->get[ID_INPUT_OBJECT_POS1].box.pos[0]
	+ INPUT_NAME_POS_X, m->get[ID_INPUT_OBJECT_EFF4].box.pos[1] + 15
	+ m->get[ID_INPUT_OBJECT_EFF4].box.heigh, c, TXT_OBJECT_MOD_TYPE);
	if (m->menu.obj->type == SPHERE)
		ft_strcpy(msg, TXT_OBJECT_TYPE_SPHERE);
	else if (m->menu.obj->type == RECTANGLE)
		ft_strcpy(msg, TXT_OBJECT_TYPE_RECTANGLE);
	else if (m->menu.obj->type == PLAN)
		ft_strcpy(msg, TXT_OBJECT_TYPE_PLAN);
	else if (m->menu.obj->type == CONE)
		ft_strcpy(msg, TXT_OBJECT_TYPE_CONE);
	else if (m->menu.obj->type == CYLINDRE)
		ft_strcpy(msg, TXT_OBJECT_TYPE_CYLINDRE);
	else if (m->menu.obj->type == COMPLEXE)
		ft_strcpy(msg, TXT_OBJECT_TYPE_COMPLEXE);
	else if (m->menu.obj->type == BOLOID)
		ft_strcpy(msg, TXT_OBJECT_TYPE_BOLOID);
	else if (m->menu.obj->type == TRIANGLE)
		ft_strcpy(msg, TXT_OBJECT_TYPE_TRIANGLE);
	else
		ft_strcpy(msg, TXT_OBJECT_TYPE_ELLIPSE);
	mlx_string_put(m->mlx, m->win, m->get[ID_INPUT_OBJECT_POS1].box.pos[0]
	+ INPUT_NAME_POS_X + 130, m->get[ID_INPUT_OBJECT_EFF4].box.pos[1] + 15
	+ m->get[ID_INPUT_OBJECT_EFF4].box.heigh, c, msg);
	scene_text_object_mod2(m, c, 0, (t_img *)NULL);
}

static void		input_text_display(t_mlx *m, t_get *g, int i, unsigned color)
{
	while (++i < GET_APP_MAX && (g = &m->get[i]))
		if (g->name && g->menu > NONE && g->menu == m->menu.id
		&& m->menu.draw == 1)
		{
			mlx_string_put(m->mlx, m->win
			, g->box.pos[0] + INPUT_NAME_POS_X
			, g->box.pos[1] + INPUT_NAME_POS_Y
			, color, g->name);
		}
}

void			scene_text_menu(t_gen *d, t_mlx *m)
{
	static char		reset[255] = {0};

	if (m->flst && (m->menu.id >= LOAD_FILE || m->menu.id <= LOAD_SPOT))
		scene_text_menu_load(m, m->flst, -1, 0);
	else if (m->menu.id == LOAD_SCENE_DEL)
		scene_text_scene_del(m, MENU_TEXT_COLOR);
	else if (m->menu.id == LOAD_OBJECT_DEL)
		scene_text_object_del(m, MENU_TEXT_COLOR);
	else if (m->menu.id == LOAD_SPOT_DEL)
		scene_text_spot_del(m, MENU_TEXT_COLOR);
	else if (m->menu.id == LOAD_OBJECT_EDIT)
		scene_text_object_mod(m, MENU_TEXT_COLOR, reset);
	else if (m->menu.id == LOAD_SPOT_EDIT)
		scene_text_spot_mod(m, MENU_TEXT_COLOR, reset);
	else if (m->menu.id == LOAD_CAMERA)
		scene_text_camera(m, MENU_TEXT_COLOR);
	input_text_display(m, (t_get *)NULL, -1, INPUT_NAME_COLOR);
	(void)d;
}
