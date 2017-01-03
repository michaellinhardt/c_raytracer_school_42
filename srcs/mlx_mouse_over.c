#include "raytra_gen.h"
#include "raystruct.h"

void	mouse_over(t_mlx *m, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
	while (m->scene_img[m->scene][++i].img)
	{

		// verification temporaire en attendant la structure menu,
		// le temps de tester le switch sur mouse over
		if ((img = &m->scene_img[m->scene][i])->status > DISABLED
		&& img->mouse.over_id > 0
		&& x >= img->mouse.top[0] && x <= img->mouse.bot[0]
		&& y >= img->mouse.top[1] && y <= img->mouse.bot[1])
		{
			layer_add(m, layer(m, 2, 0)
			, &m->scene_img[m->scene][img->mouse.over_id]);
		}
	}
}
