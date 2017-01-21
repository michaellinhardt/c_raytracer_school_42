#include "raystruct.h"

void			menu_edit_mod_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	if (m->menu.id >= LOAD_SCENE && m->menu.id < LOAD_OBJECT)
	{
		m->get[ID_INPUT_MOD_SCENE_NAME].target.ptr_str = &d->sc->name;
		m->get[ID_INPUT_SCENE_AMBIANCE1].target.ptr_double = &d->sc->amb[0];
		m->get[ID_INPUT_SCENE_AMBIANCE2].target.ptr_double = &d->sc->amb[1];
		m->menu.next = LOAD_SCENE_EDIT;
	}
	else if (m->menu.id >= LOAD_OBJECT && m->menu.id < LOAD_SPOT)
	{
		m->get[ID_INPUT_OBJECT_NAME].target.ptr_str = &m->menu.obj->name;
		m->get[ID_INPUT_OBJECT_POS1].target.ptr_double = &m->menu.obj->pos[0];
		m->get[ID_INPUT_OBJECT_POS2].target.ptr_double = &m->menu.obj->pos[1];
		m->get[ID_INPUT_OBJECT_POS3].target.ptr_double = &m->menu.obj->pos[2];
		m->get[ID_INPUT_OBJECT_POS4].target.ptr_double = &m->menu.obj->pos[3];
		m->get[ID_INPUT_OBJECT_POS5].target.ptr_double = &m->menu.obj->pos[4];
		m->get[ID_INPUT_OBJECT_POS6].target.ptr_double = &m->menu.obj->pos[5];
		m->get[ID_INPUT_OBJECT_SIZE1].target.ptr_double = &m->menu.obj->size[0];
		m->get[ID_INPUT_OBJECT_SIZE2].target.ptr_double = &m->menu.obj->size[1];
		m->get[ID_INPUT_OBJECT_SIZE3].target.ptr_double = &m->menu.obj->size[2];
		m->get[ID_INPUT_OBJECT_EFF1].target.ptr_double = &m->menu.obj->eff[0];
		m->get[ID_INPUT_OBJECT_EFF2].target.ptr_double = &m->menu.obj->eff[1];
		m->get[ID_INPUT_OBJECT_EFF3].target.ptr_double = &m->menu.obj->eff[2];
		m->get[ID_INPUT_OBJECT_EFF4].target.ptr_double = &m->menu.obj->eff[3];
		m->get[ID_INPUT_OBJECT_EFF5].target.ptr_double = &m->menu.obj->eff[4];
		m->get[ID_INPUT_OBJECT_EFF6].target.ptr_double = &m->menu.obj->eff[5];
		m->get[ID_INPUT_OBJECT_COLOR].target.ptr_int = &m->menu.obj->c_o;
		m->menu.next = LOAD_OBJECT_EDIT;
	}
}
