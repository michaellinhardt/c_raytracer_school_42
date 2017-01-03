#include "raytra_gen.h"

void	mouse_release(t_mlx *m, int btn, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
	while (m->scene_img[m->scene][++i].img)
	{
		if ((img = &m->scene_img[m->scene][i])->status > IMG_ANIM
		&& x >= img->mouse.top[0] && x <= img->mouse.bot[0]
		&& y >= img->mouse.top[1] && y <= img->mouse.bot[1]
		&& (btn == img->mouse.btn || img->mouse.btn == 3))
			img->mouse.action((void *)m);
	}
}
