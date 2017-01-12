#include "raytra_gen.h"
#include "raystruct.h"

void	mouse_over(t_mlx *m, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
	while (m->scene_img[m->scene][++i].img)
	{
		if ((img = &m->scene_img[m->scene][i])->status > DISABLED
		&& img->mouse.over_id > 0 && area(img, NULL, x, y))
		{
			if (img->status == MENU && (m->menu.draw == -1
			|| (m->menu.draw == 1 && img->menu != NONE
			&& img->menu != m->menu.id)))
				continue ;
			layer_add(m, layer(m, 2, 0)
				, &m->scene_img[m->scene][img->mouse.over_id]);
		}
	}
}
