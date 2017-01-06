#include "raystruct.h"

static void		calc_margin(t_mlx *m, int *marginx, int *marginy)
{
	int		imagex;
	int		imagey;

	imagex = m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW].width;
	imagey = m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW].heigh;
	*marginx = (MENU_LOAD_SIZE_X - (MENU_LOAD_X_MAX * imagex))
	/ (MENU_LOAD_X_MAX + 1);
	*marginy = (MENU_LOAD_SIZE_Y - (MENU_LOAD_Y_MAX * imagey))
	/ (MENU_LOAD_Y_MAX + 1);
}

static void		set_elem(t_mlx *m, t_flst *elem, int x, int y)
{
	static int		marginx = -1;
	static int		marginy = -1;
	static int		sizex = -1;
	static int		sizey = -1;

	if (marginx == -1)
	{
		calc_margin(m, &marginx, &marginy);
		sizex = m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW].width;
		sizey = m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW].heigh;
	}
	elem->top[0] = MENU_LOAD_START_X + ((x + 1) * marginx) + (x * sizex);
	elem->top[1] = MENU_LOAD_START_Y + ((y + 1) * marginy) + (y * sizey);
	elem->bot[0] = elem->top[0] + sizex;
	elem->bot[1] = elem->top[1] + sizey;
	m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW].pos[0] = elem->top[0];
	m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW].pos[1] = elem->top[1];
	layer_add(m, layer(m, 1, 0), &m->scene_img[1][MENU_LOAD_ID_IMG_PREVIEW]);
	mlx_string_put(m->mlx, m->win, elem->top[0],
	elem->bot[1] + 10, 0xFFFFFF, elem->path);
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
			// ft_printf("elem: %s\n", lst->path);
			set_elem(m, lst, x, y);
			lst = lst->n;
		}
		x = -1;
	}
	if (lst && lst->n)
		m->scene_img[1][7].status = MENU;
	else
		m->scene_img[1][7].status = DISABLED;
	// ft_printf("--\n");
}
