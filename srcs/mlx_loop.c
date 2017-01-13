#include "raystruct.h"

int		loop(t_mlx *m, char etat)
{
	if (m->loop && m->loopstop != 0)
		return (1);
	else if (m->loop != etat)
		m->loop = etat;
	return (1);
}

int		loopstop(t_mlx *m, char total)
{
	m->loopstop = total;
	if (m->loopstop && !m->loop)
		loop(m, 1);
	return (1);
}

int		loop_hook(t_gen *d)
{
	t_mlx *m;

	m = &d->mlx;
	if (USLEEP_BOOL && m->loop == 0 && !usleep(USLEEP_TIME))
		return (0);
	if (m->loopstop != 0 && --m->loopstop < 1 && m->loop != 0)
		loop(&d->mlx, 0);
	scene_img_load(d, &d->mlx);
	scene_btn(d, m, (t_img *)NULL);
	scene_build(m, layer(m, 1, 0), (t_img *)NULL, -1);
	scene(d, m);
	return (0);
}
