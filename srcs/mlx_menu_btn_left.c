#include "raystruct.h"

void			menu_btn_left(void *ptr)
{
	t_mlx	*m;

	m = ptr;
	if (m->scene == RT && m->menu.id == LOAD_FILE && m->menu.draw == 1)
		menu_load_btn_prev(ptr);
	(void)m;
}
