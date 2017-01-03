#include "raystruct.h"

void		scene(t_gen *d, t_mlx *m)
{
	if (m->scene == INTRO)
		scene_0_intro(m);
	else if (m->scene == RT)
		scene_1_rt(m);
	(void)d;
	(void)m;
}
