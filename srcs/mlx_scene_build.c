#include "raystruct.h"

void		scene_build(t_mlx *m, t_img *lay, t_img *img, int i)
{
	while (m->scene_img[m->scene][++i].img)
	{
		if (((img = &m->scene_img[m->scene][i])->status > MENU)
		|| (m->menu.draw == 1 && img->status == MENU
		&& (img->menu_id == 0 || img->menu_id == m->menu.id)))
			layer_add(m, lay, img);
	}
}
