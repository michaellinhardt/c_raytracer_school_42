#include "raytra_gen.h"
#include "raystruct.h"

static int		preview_clic(t_mlx *m, t_flst *elem, int x, int y)
{
	int		i;
	t_img	*img;

	i = MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX;
	img = &m->scene_img[m->scene][MENU_LOAD_ID_IMG_PREVIEW_CLIC];
	while (elem && --i >= 0)
	{
		if (x >= elem->top[0] && x <= elem->bot[0] && y >= elem->top[1]
		&& y <= elem->bot[1])
		{
			img->pos[0] = elem->top[0];
			img->pos[1] = elem->top[1];
			layer_add(m, layer(m, 3, 0), img);
		}
		elem = elem->n;
	}
	return (0);
}

void			mouse_release(t_mlx *m, int btn, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
	if (m->scene == RT && m->menu.id == LOAD_FILE && m->menu.draw == 1
	&& btn == 1 && preview_clic(m, m->flst, x, y))
		return ;
	while (m->scene_img[m->scene][++i].img)
	{
		if ((img = &m->scene_img[m->scene][i])->status == MENU
		&& m->menu.draw == 1
		&& (m->menu.id == img->menu || img->menu == NONE)
		&& x >= img->mouse.top[0] && x <= img->mouse.bot[0]
		&& y >= img->mouse.top[1] && y <= img->mouse.bot[1]
		&& (btn == img->mouse.btn || img->mouse.btn == 3))
		{
			if (img->mouse.click_id > 0)
				layer_add(m, layer(m, 3, 0)
					, &m->scene_img[m->scene][img->mouse.click_id]);
			if (img->mouse.action)
				img->mouse.action((void *)m);
			return ;
		}
	}
}
