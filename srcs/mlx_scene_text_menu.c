#include "raystruct.h"

static void		scene_text_menu_load(t_mlx *m, t_flst *elem, int i, int color)
{
	char			name[MENU_LOAD_PREVIEW_NAME_SIZE_MAX];
	size_t			len;

	while (elem && ++i < MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX)
	{
		if (!elem->path && ((elem = elem->n) || 1))
			continue ;
		if ((len = ft_strlen(elem->path)) > MENU_LOAD_PREVIEW_NAME_SIZE_MAX)
		{
			ft_memset(name, '.', MENU_LOAD_PREVIEW_NAME_SIZE_MAX);
			ft_memcpy(name, elem->path, MENU_LOAD_PREVIEW_NAME_SIZE_MAX - 2);
			len = MENU_LOAD_PREVIEW_NAME_SIZE_MAX;
		}
		else
			ft_memcpy(name, elem->path, len);
		name[len] = '\0';
		color = 0xFFFFFF;
		if (elem->actif == 1)
			color = 0xFF0000;
		else if (elem->over)
			color = 0x00FFFF;
		mlx_string_put(m->mlx, m->win, elem->top[0] + MENU_LOAD_TEXT_MARGIN_X,
		elem->bot[1] + MENU_LOAD_TEXT_MARGIN_Y, color, name);
		elem = elem->n;
	}
}

static void		scene_text_camera(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_CAMERA_BOX].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_CAMERA_BOX].pos[1] + 25
	, c, TXT_CAMERA_MOD_TITLE);
}

static void		scene_text_scene_del(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1] + 38
	, c, TXT_SCENE_DEL_VALID);
}

static void		scene_text_object_del(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[1] + 38
	, c, TXT_OBJECT_DEL_VALID);
}

static void		scene_text_spot_del(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[1] + 38
	, c, TXT_SPOT_DEL_VALID);
}

static void		scene_text_object_mod2(t_mlx *m, int c, int i, t_img *img)
{
	char		str[9][255];

	ft_strcpy(str[0], TXT_OBJECT_TYPE_SPHERE);
	ft_strcpy(str[1], TXT_OBJECT_TYPE_RECTANGLE);
	ft_strcpy(str[2], TXT_OBJECT_TYPE_PLAN);
	ft_strcpy(str[3], TXT_OBJECT_TYPE_CONE);
	ft_strcpy(str[4], TXT_OBJECT_TYPE_CYLINDRE);
	ft_strcpy(str[5], TXT_OBJECT_TYPE_COMPLEXE);
	ft_strcpy(str[6], TXT_OBJECT_TYPE_BOLOID);
	ft_strcpy(str[7], TXT_OBJECT_TYPE_TRIANGLE);
	ft_strcpy(str[8], TXT_OBJECT_TYPE_ELLIPSE);
	while (++i < 10)
	{
		img = &m->scene_img[1][(IB_OBJECT_MOD_TYPE_SELECT + i)];
		mlx_string_put(m->mlx, m->win, img->pos[0] + 10, img->pos[1] + 10
		, c, str[i - 1]);
	}
}

static void		scene_text_spot_mod2(t_mlx *m, int c, int i, t_img *img)
{
	char		str[2][255];

	ft_strcpy(str[0], TXT_SPOT_TYPE_DIIR);
	ft_strcpy(str[1], TXT_SPOT_TYPE_POINT);
	while (++i < 3)
	{
		img = &m->scene_img[1][(IMENU_EDIT_SPOT_BOX + i)];
		mlx_string_put(m->mlx, m->win, img->pos[0] + 10, img->pos[1] + 10
		, c, str[i - 1]);
	}
}

static void		scene_text_spot_mod(t_mlx *m, int c, char msg[512])
{
	mlx_string_put(m->mlx, m->win, m->get[ID_INPUT_SPOT_POS1].box.pos[0]
	+ INPUT_NAME_POS_X, m->get[ID_INPUT_SPOT_POS4].box.pos[1] + 15
	+ m->get[ID_INPUT_OBJECT_POS4].box.heigh, c, TXT_SPOT_MOD_TYPE);
	if (m->menu.spot->type == DIIR)
		ft_strcpy(msg, TXT_SPOT_TYPE_DIIR);
	else
		ft_strcpy(msg, TXT_SPOT_TYPE_POINT);
	mlx_string_put(m->mlx, m->win, m->get[ID_INPUT_SPOT_POS1].box.pos[0]
	+ INPUT_NAME_POS_X + 130, m->get[ID_INPUT_SPOT_POS4].box.pos[1] + 15
	+ m->get[ID_INPUT_SPOT_POS4].box.heigh, c, msg);
	scene_text_spot_mod2(m, c, 0, (t_img *)NULL);
}

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
