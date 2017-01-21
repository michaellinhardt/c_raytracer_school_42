#include "raystruct.h"

void			menu_camera_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	d = gen;
	m = mlx;
	ft_printf("camera btn open\n");
	redraw(d, m, 1);
	(void)m;
	(void)gen;
	(void)mlx;
}
