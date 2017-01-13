#include "raystruct.h"

void			menu_edit_add_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	m->menu.next = LOAD_SCENE_ADD;
	(void)m;
	(void)gen;
	(void)mlx;
}
