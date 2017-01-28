#include "raystruct.h"

void			menu_btn_right(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->scene == RT && m->menu.draw == 1)
		menu_load_btn_next(gen, mlx);
	(void)gen;
	(void)mlx;
}
