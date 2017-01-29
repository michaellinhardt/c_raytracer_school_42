#include "raystruct.h"

void			menu_filter_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	m->menu.next = LOAD_FILTER;
	(void)gen;
	(void)mlx;
}

void			menu_filter_checkbox_btn_on(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	notif(m, N_NORMAL, "checkbox click on");
	(void)m;
	(void)gen;
	(void)mlx;
}

void			menu_filter_checkbox_btn_off(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	notif(m, N_NORMAL, "checkbox click off");
	(void)m;
	(void)gen;
	(void)mlx;
}

void			menu_filter_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	notif(m, N_NORMAL, "filter click ok");
	(void)m;
	(void)gen;
	(void)mlx;
}

void			menu_filter_btn_cancel(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	notif(m, N_NORMAL, "filter click cancel");
	(void)m;
	(void)gen;
	(void)mlx;
}
