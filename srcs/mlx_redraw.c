#include "raystruct.h"

void			redraw(t_gen *d, t_mlx *m, int loading)
{
	if (loading == 1)
		m->menu.loading = MENU_LOAD_WAIT_BEFORE_LOAD - 1;
	m->menu.draw = -1;
	ft_strdel(&d->sc->data);
}
