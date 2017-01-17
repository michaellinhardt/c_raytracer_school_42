#include "raystruct.h"

void			menu_edit_switch_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	menu_scene_open_order(d, m);
	(void)d;
	(void)m;
	(void)gen;
	(void)mlx;
}
