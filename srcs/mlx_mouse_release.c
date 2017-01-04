#include "raytra_gen.h"
#include "raystruct.h"

void	mouse_release(t_mlx *m, int btn, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
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
		}
	}
}
