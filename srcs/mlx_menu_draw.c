#include "raystruct.h"

static void		calc_margin(t_mlx *m, int *marginx, int *marginy)
{
	int		imagex;
	int		imagey;

	imagex = m->scene_img[1][ID_IMG_PREVIEW].width;
	imagey = m->scene_img[1][ID_IMG_PREVIEW].heigh;
	*marginx = (MENU_LOAD_SIZE_X - (MENU_LOAD_X_MAX * imagex))
	/ (MENU_LOAD_X_MAX + 1);
	*marginy = (MENU_LOAD_SIZE_Y - (MENU_LOAD_Y_MAX * imagey))
	/ (MENU_LOAD_Y_MAX + 1);
}

static t_img	*set_img(t_mlx *m, t_flst *elem, t_img *img)
{
	elem->over = 0;
	if (area(NULL, elem, m->input.mouse.over_x, m->input.mouse.over_y))
	{
		elem->over = 1;
		img = &m->scene_img[1][ID_IMG_PREVIEW_OVER];
	}
	else
		img = &m->scene_img[1][ID_IMG_PREVIEW];
	img->pos[0] = elem->top[0];
	img->pos[1] = elem->top[1];
	return (img);
}

static void		push_elem(t_mlx *m, t_flst *elem, t_img *img)
{
	if (elem->preview.img)
	{
		img = &elem->preview;
		img->pos[0] = elem->top[0] + 7;
		img->pos[1] = elem->top[1] + 7;
	}
	else
	{
		img = &m->scene_img[1][ID_IMG_PREVIEW_NO_IMG];
		img->pos[0] = elem->top[0] + 46;
		img->pos[1] = elem->top[1] + 19;
	}
	layer_add(m, layer(m, 1, 0), img);
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
		sizex = m->scene_img[1][ID_IMG_PREVIEW].width;
		sizey = m->scene_img[1][ID_IMG_PREVIEW].heigh;
	}
	elem->top[0] = MENU_LOAD_START_X + ((x + 1) * marginx) + (x * sizex);
	elem->top[1] = MENU_LOAD_START_Y + ((y + 1) * marginy) + (y * sizey);
	elem->bot[0] = elem->top[0] + sizex;
	elem->bot[1] = elem->top[1] + sizey;
	layer_add(m, layer(m, 1, 0), set_img(m, elem, (t_img *)NULL));
	push_elem(m, elem, (t_img *)NULL);
}

void			menu_draw(t_mlx *m, t_flst *lst, int x, int y)
{
	if (lst->p)
		m->scene_img[1][ID_IMG_BTN_ARROW_LEFT].status = MENU;
	else
		m->scene_img[1][ID_IMG_BTN_ARROW_LEFT].status = DISABLED;
	while (++y < MENU_LOAD_Y_MAX)
	{
		while (lst && ++x < MENU_LOAD_X_MAX)
		{
			set_elem(m, lst, x, y);
			lst = lst->n;
		}
		x = -1;
	}
	if (lst && lst->n)
		m->scene_img[1][ID_IMG_BTN_ARROW_RIGHT].status = MENU;
	else
		m->scene_img[1][ID_IMG_BTN_ARROW_RIGHT].status = DISABLED;
}
