#include "raystruct.h"

void			menu_edit_add_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->menu.id >= LOAD_SCENE && m->menu.id < LOAD_OBJECT)
		m->menu.next = LOAD_SCENE_ADD;
	else if (m->menu.id >= LOAD_OBJECT && m->menu.id < LOAD_SPOT)
		m->menu.next = LOAD_OBJECT_ADD;
	(void)m;
	(void)gen;
	(void)mlx;
}
