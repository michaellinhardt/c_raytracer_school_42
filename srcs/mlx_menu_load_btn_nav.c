#include "raystruct.h"

void			menu_load_btn_next(void *ptr)
{
	t_mlx	*m;
	int		target;

	m = ptr;
	target = m->flst->id + (MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX);
	if (target > (1 + m->total_file - (MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX)))
		target = 1 + m->total_file - (MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX);
	while (m->flst->id != target)
		m->flst = m->flst->n;
}
