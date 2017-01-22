#include "raystruct.h"

void			menu_spot_mod_btn_type(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	m->menu.spot->type = m->menu.spot_type;
	(void)m;
	(void)gen;
	(void)mlx;
}
