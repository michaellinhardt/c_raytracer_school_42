#include "raystruct.h"

void			menu_scene_del_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	t_scene	*sc;

	m = mlx;
	d = gen;
	if (!d->sc)
		menu_edit_add_btn_open(gen, mlx);
	else
	{
		sc = d->sc;
		d->sc = d->sc->next;
		sc->next = d->sc_off;
		d->sc_off = sc;
		m->menu.scene = NULL;
		menu_reset_obj_plan(m);
		menu_scene_del_btn_cancel(gen, mlx);
	}
}

void			menu_scene_del_btn_cancel(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	if (d->sc)
		menu_edit_mod_btn_open(gen, mlx);
	else
		menu_edit_add_btn_open(gen, mlx);
}
