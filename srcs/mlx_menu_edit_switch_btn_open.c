#include "raystruct.h"

void			menu_edit_switch_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	if (m->menu.id >= LOAD_SCENE && m->menu.id < LOAD_OBJECT)
		menu_scene_open_order(d, m);
	else if (m->menu.id >= LOAD_OBJECT && m->menu.id < LOAD_SPOT)
		menu_object_open_order(d, m);
	else if (m->menu.id >= LOAD_SPOT && m->menu.id < LOAD_CAMERA)
		menu_spot_open_order(d, m);
	(void)d;
	(void)m;
	(void)gen;
	(void)mlx;
}
