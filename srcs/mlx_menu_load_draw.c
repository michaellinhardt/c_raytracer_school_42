#include "raystruct.h"

static void		set_elem(t_flst *elem, int x, int y)
{
	// elem->top[0] = MENU_LOAD_START_X +
}

void			menu_load_draw(t_mlx *m, t_flst *lst, int x, int y)
{
	if (lst->p)
		m->scene_img[1][4].status = MENU;
	else
		m->scene_img[1][4].status = DISABLED;
	while (++y < MENU_LOAD_Y_MAX)
	{
		while (lst && ++x < MENU_LOAD_X_MAX)
		{
			set_elem(lst, x, y);
			lst = lst->n;
		}
		x = -1;
	}
	if (lst && lst->n)
		m->scene_img[1][7].status = MENU;
	else
		m->scene_img[1][7].status = DISABLED;
	ft_printf("--\n");
}
