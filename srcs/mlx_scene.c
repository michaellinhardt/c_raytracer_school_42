#include "raystruct.h"

void		scene(t_gen *d, t_mlx *m)
{
	if (m->scene == INTRO)
		mlx_scene_0_intro(d, m);
	// else if (m->scene == INTRO)
	// 	scene_0_intro(d, m);
	(void)d;
	(void)m;
}
