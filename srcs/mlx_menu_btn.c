#include "raystruct.h"

static void		s(t_mlx *m, int boolean, int trueval, int falseval)
{
	if (boolean)
	{
		m->scene_img[1][trueval].status = MENU;
		m->scene_img[1][falseval].status = DISABLED;
	}
	else
	{
		m->scene_img[1][trueval].status = DISABLED;
		m->scene_img[1][falseval].status = MENU;
	}
}

static void		scene_btn_sub(t_gen *d, t_mlx *m, t_menu *e)
{
	s(m, (!d->sc ? 1 : 0), IB_SAVE_OFF, IB_SAVE);
	s(m, (!d->sc ? 1 : 0), IB_GEN_DATA_OFF, IB_GEN_DATA);
	s(m, (!d->sc || !d->sc->data ? 1 : 0), IB_GEN_BMP_OFF, IB_GEN_BMP);
	if (m->menu.id == LOAD_FILE)
	{
		s(m, 1, IB_E_MOD_OFF, IB_E_MOD);
		s(m, 1, IB_E_ADD_OFF, IB_E_ADD);
		s(m, 1, IB_E_SWITCH_OFF, IB_E_SWITCH);
		s(m, 1, IB_E_DEL_OFF, IB_E_DEL);
	}
	else if (e->id >= LOAD_SCENE && e->id < LOAD_OBJECT)
	{
		s(m, (!d->sc ? 1 : 0), IB_E_MOD_OFF, IB_E_MOD);
		s(m, 0, IB_E_ADD_OFF, IB_E_ADD);
		s(m, (!d->sc ? 1 : 0), IB_E_SWITCH_OFF, IB_E_SWITCH);
		s(m, (!d->sc ? 1 : 0), IB_E_DEL_OFF, IB_E_DEL);
	}
	else if (e->id >= LOAD_OBJECT && e->id < LOAD_SPOT)
	{
		s(m, (!m->menu.obj ? 1 : 0), IB_E_MOD_OFF, IB_E_MOD);
		s(m, 0, IB_E_ADD_OFF, IB_E_ADD);
		s(m, (!d->sc ? 1 : 0), IB_E_SWITCH_OFF, IB_E_SWITCH);
		s(m, (!((d->sc)->obj)->next || !m->menu.obj ? 1 : 0), IB_E_DEL_OFF, IB_E_DEL);
	}
	else if (e->id >= LOAD_SPOT && e->id < LOAD_CAMERA)
	{
		s(m, (!m->menu.spot ? 1 : 0), IB_E_MOD_OFF, IB_E_MOD);
		s(m, 0, IB_E_ADD_OFF, IB_E_ADD);
		s(m, (!d->sc ? 1 : 0), IB_E_SWITCH_OFF, IB_E_SWITCH);
		s(m, (!((d->sc)->spot)->next || !m->menu.spot ? 1 : 0), IB_E_DEL_OFF, IB_E_DEL);
	}
	else if (e->id == LOAD_CAMERA)
	{
		s(m, 1, IB_E_MOD_OFF, IB_E_MOD);
		s(m, 1, IB_E_ADD_OFF, IB_E_ADD);
		s(m, 1, IB_E_SWITCH_OFF, IB_E_SWITCH);
		s(m, 1, IB_E_DEL_OFF, IB_E_DEL);
	}
	(void)d;
	(void)m;
}

void			scene_btn(t_gen *d, t_mlx *m, t_img *img, t_menu *e)
{
	s(m, (!e->scene ? 1 : 0), IB_OBJECT_OFF, IB_OBJECT);
	s(m, (!e->scene ? 1 : 0), IB_SPOT_OFF, IB_SPOT);
	s(m, (!e->scene ? 1 : 0), IB_CAMERA_OFF, IB_CAMERA);
	scene_btn_sub(d, m, e);
	(void)d;
	(void)m;
	(void)img;
}
