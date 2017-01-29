#include "raystruct.h"

void			menu_filter_checkbox_btn(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	notif(m, N_NORMAL, "checkbox click");
	(void)m;
	(void)gen;
	(void)mlx;
}
