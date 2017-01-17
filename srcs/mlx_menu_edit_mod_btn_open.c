#include "raystruct.h"

void			menu_edit_mod_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	ft_printf("mod btn clic\n");
	m->get[ID_INPUT_MOD_SCENE_NAME].target.ptr_str = &d->sc->name;
	m->get[ID_INPUT_SCENE_AMBIANCE1].target.ptr_double = &d->sc->amb[0];
	m->get[ID_INPUT_SCENE_AMBIANCE2].target.ptr_double = &d->sc->amb[1];
	m->menu.next = LOAD_SCENE_EDIT;
}
