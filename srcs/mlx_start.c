# include "raystruct.h"
# include "raytra_gen.h"

int				red_cross(void)
{
	exit(0);
	return (0);
}

static void		init_project(t_mlx *m)
{
	layer(m, 1, 2);
	layer(m, 2, 2);
	// parse_scene(d, "./scene/mika.rt");
	// m->draw_rt = 1;
	loop(m, 1);
	// m->scene++;
}

void			mlx_start(t_gen *d, t_mlx *m)
{
	ft_bzero(m, sizeof(t_mlx));
	m->winx = W_X;
	m->winy = W_Y;
	if (!(m->mlx = mlx_init()))
		error(2, "mlx_init()");
	if (!(m->win = mlx_new_window(m->mlx, m->winx, m->winy, WIN_TITLE)))
		error(2, "mlx_new_window()");
	mlx_hook(m->win, 2, (1L << 0), keyp_hook, d);
	mlx_hook(m->win, 3, (1L << 1), keyr_hook, d);
	mlx_hook(m->win, 4, (1L << 2), mousep_hook, d);
	mlx_hook(m->win, 5, (1L << 3), mouser_hook, d);
	mlx_hook(m->win, 6, (1L << 0), mouseo_hook, d);
	mlx_hook(m->win, 17, (1L << 17), &red_cross, d);
	mlx_loop_hook(m->mlx, loop_hook, d);
	init_project(m);
	mlx_loop(m->mlx);
}
