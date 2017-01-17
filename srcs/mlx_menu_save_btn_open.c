#include "raystruct.h"

void			menu_save_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	notif(m, N_NORMAL, "clic save btn");
	(void)m;
	(void)gen;
	(void)mlx;
}
