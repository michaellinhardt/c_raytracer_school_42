#include "raystruct.h"

void		scene(t_gen *d, t_mlx *m)
{
	if (m->scene == INTRO)
		scene_0_intro(m);
	else if (m->scene == RT)
		ft_printf("rt scene\n"), exit(0);
	(void)d;
	(void)m;
}
