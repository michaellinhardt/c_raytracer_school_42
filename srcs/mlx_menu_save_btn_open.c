#include "raystruct.h"

void			menu_save_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	ft_printf("save btn open\n");
	notif(m, N_NORMAL, "clic save btn");
	(void)m;
	(void)gen;
	(void)mlx;
}
