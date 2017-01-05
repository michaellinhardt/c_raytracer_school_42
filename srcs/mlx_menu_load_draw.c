#include "raystruct.h"

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
			ft_printf("list: %s\n", lst->path);
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
