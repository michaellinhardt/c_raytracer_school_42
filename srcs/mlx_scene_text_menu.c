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

static void		scene_text_scene_add(t_mlx *m, int c)
{

	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_ADD_SCENE_BOX].pos[0] + 15
	, m->scene_img[1][IMENU_ADD_SCENE_BOX].pos[1] + 8
	, c, TXT_SCENE_ADD_NAME);
}

static void		scene_text_scene_del(t_mlx *m, int c)
{

	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1] + 38
	, c, TXT_SCENE_DEL_VALID);
}

static void		scene_text_scene_mod(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX].pos[0] + 15
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX].pos[1] + 8
	, c, TXT_SCENE_MOD_NAME);
	mlx_string_put(m->mlx, m->win
	, m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[0] + 6
	, m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[1] - 23
	, c, TXT_SCENE_MOD_AMB1);
	mlx_string_put(m->mlx, m->win
	, m->get[ID_INPUT_SCENE_AMBIANCE2].box.pos[0] + 6
	, m->get[ID_INPUT_SCENE_AMBIANCE2].box.pos[1] - 23
	, c, TXT_SCENE_MOD_AMB2);
}

void			scene_text_menu(t_gen *d, t_mlx *m)
{
	if (m->flst && (m->menu.id >= LOAD_FILE || m->menu.id <= LOAD_SPOT))
		scene_text_menu_load(m, m->flst, -1, 0);
	else if (m->menu.id == LOAD_SCENE_ADD)
		scene_text_scene_add(m, MENU_TEXT_COLOR);
	else if (m->menu.id == LOAD_SCENE_EDIT)
		scene_text_scene_mod(m, MENU_TEXT_COLOR);
	else if (m->menu.id == LOAD_SCENE_DEL)
		scene_text_scene_del(m, MENU_TEXT_COLOR);
	(void)d;
}
