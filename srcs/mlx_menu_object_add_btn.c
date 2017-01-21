#include "raystruct.h"

void			menu_object_add_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	t_obj	*obj;

	m = mlx;
	d = gen;
	if (!m->menu.new_object || !ft_strcmp(m->menu.new_object
	, TXT_OBJECT_ADD_NAME_DEFAUT))
		notif(m, N_WARNING, "you must enter a new object name");
	else if (ft_strlen(m->menu.new_object) < 3)
		notif(m, N_WARNING, "object name must have at least 3 char");
	else
	{
		if (!(obj = (t_obj *)ft_memalloc(sizeof(t_obj))))
			error(2, "ft_memalloc(t_obj)");
		ft_memcpy(obj, d->sc->obj, sizeof(t_obj));
		obj->name = m->menu.new_object;
		obj->type = SPHERE;
		m->menu.new_object = ft_strdup(TXT_OBJECT_ADD_NAME_DEFAUT);
		obj->next = d->sc->obj;
		d->sc->obj = obj;
		menu_object_open_order(d, m);
	}
}
