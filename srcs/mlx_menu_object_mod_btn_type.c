#include "raystruct.h"

void			menu_object_mod_btn_type(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	m->menu.obj->type = m->menu.obj_type;
	(void)m;
	(void)gen;
	(void)mlx;
}
