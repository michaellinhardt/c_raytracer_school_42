#include "raystruct.h"

static void	scene_text_menu_load(t_mlx *m, t_flst *elem, int i, int color)
{
	static int		max = -1;
	char			name[MENU_LOAD_PREVIEW_NAME_SIZE_MAX];
	size_t			len;

	if (max == -1)
		max = MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX;
	while (elem && ++i < max)
	{
		len = ft_strlen(elem->path);
		if (len > MENU_LOAD_PREVIEW_NAME_SIZE_MAX)
		{
			ft_memset(name, '.', MENU_LOAD_PREVIEW_NAME_SIZE_MAX);
			ft_memcpy(name, elem->path, MENU_LOAD_PREVIEW_NAME_SIZE_MAX - 2);
			len = MENU_LOAD_PREVIEW_NAME_SIZE_MAX;
		}
		else
			ft_memcpy(name, elem->path, len);
		name[len] = '\0';
		if (m->input.mouse.over_x >= elem->top[0]
		&& m->input.mouse.over_x <= elem->bot[0]
		&& m->input.mouse.over_y >= elem->top[1]
		&& m->input.mouse.over_y <= elem->bot[1])
			color = 0xFF0000;
		else
			color = 0xFFFFFF;
		mlx_string_put(m->mlx, m->win, elem->top[0] + MENU_LOAD_TEXT_MARGIN_X,
		elem->bot[1] + MENU_LOAD_TEXT_MARGIN_Y, color, name);
		elem = elem->n;
	}
}

void		scene_text(t_mlx *m)
{
	if (m->scene == RT && m->menu.id == LOAD_FILE && m->menu.draw == 1)
		scene_text_menu_load(m, m->flst, -1, 0);
}
