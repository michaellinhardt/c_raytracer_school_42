#include "raystruct.h"

void			menu_filter_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	m->menu.next = LOAD_FILTER;
	(void)gen;
}

void			menu_filter_checkbox_btn(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->menu.filter[m->menu.filter_id])
		m->menu.filter[m->menu.filter_id] = 0;
	else
		m->menu.filter[m->menu.filter_id] = 1;
	(void)gen;
}

void			menu_filter_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	(void)m;
	(void)d;
	(void)gen;
}

void			menu_filter_btn_cancel(void *gen, void *mlx)
{
	t_mlx	*m;
	int		i;

	m = mlx;
	i = -1;
	while (++i < 14)
		m->menu.filter[i] = 0;
	(void)gen;
}

void			menu_filter(t_mlx *m, int i)
{
	if (m->menu.draw == -1 || m->menu.id != LOAD_FILTER)
		return ;
	while (++i < 14)
		if (m->menu.filter[i])
		{
			m->scene_img[1][IB_FILTER1_ON + i].status = MENU;
			m->scene_img[1][IB_FILTER1_OFF + i].status = DISABLED;
		}
		else
		{
			m->scene_img[1][IB_FILTER1_ON + i].status = DISABLED;
			m->scene_img[1][IB_FILTER1_OFF + i].status = MENU;
		}
}
