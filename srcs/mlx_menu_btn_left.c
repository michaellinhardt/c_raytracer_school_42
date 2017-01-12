#include "raystruct.h"

void			menu_btn_left(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->scene == RT && m->menu.id == LOAD_FILE && m->menu.draw == 1)
		menu_load_btn_prev(gen, mlx);
	(void)gen;
	(void)mlx;
}
