#include "raystruct.h"

void		scene_build(t_mlx *m, t_img *lay, t_img *img, int i)
{
	layer(m, 1, 1);
	if (m->scene == RT && m->menu.id == LOAD_FILE && m->menu.draw == 1)
		menu_load_draw(m, m->flst, -1, -1);
	while (m->scene_img[m->scene][++i].img)
	{
		if (((img = &m->scene_img[m->scene][i])->status > MENU)
		|| (m->menu.draw == 1 && img->status == MENU
		&& (img->menu == NONE || img->menu == m->menu.id)))
			layer_add(m, lay, img);
	}
}
