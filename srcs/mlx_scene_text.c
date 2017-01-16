#include "raystruct.h"

void			scene_text(t_gen *d, t_mlx *m)
{
	if (m->scene == RT && m->menu.draw == 1)
	{
		scene_text_menu(d, m);
		scene_text_input(m, (t_get *)NULL, -1);
	}
}
