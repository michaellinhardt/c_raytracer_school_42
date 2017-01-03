#include "raystruct.h"

void		scene_build(t_mlx *m, t_img *lay, t_img *img, int i)
{
	while (m->scene_img[m->scene][++i].img)
	{
		if ((img = &m->scene_img[m->scene][i])->status > MENU)
			layer_add(m, lay, img);
	}
}
