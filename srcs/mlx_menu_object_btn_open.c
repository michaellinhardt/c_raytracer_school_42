#include "raystruct.h"

static void		load_preview(t_mlx *m, t_flst *elem)
{
	(void)m;
	(void)elem;
}

static void		build_list(t_mlx *m, t_flst *new, t_obj *obj)
{
	while (obj)
	{
		if (!(new = (t_flst *)ft_memalloc(sizeof(t_flst))))
			error(2, "malloc t_flst struct");
		if (!obj->name || ft_strlen(obj->name) == 0)
			new->path = ft_strdup("Unknow..");
		else
			new->path = ft_strdup(obj->name);
		if (!m->flst && (m->flst = new) && (!(new->p = (t_flst *)NULL)))
				new->n = (t_flst *)NULL;
		else if ((m->flst->p = new)
		&& (new->n = m->flst)
		&& (!(new->p = NULL)))
			m->flst = new;
		m->flst->obj = obj;
		load_preview(m, m->flst);
		obj = obj->next;
	}
}

static void		menu_object_open_order(t_gen *d, t_mlx *m)
{
	t_flst	*lst;
	int		total;

	menu_list_free(m, m->flst, (t_flst *)NULL);
	m->flst = NULL;
	build_list(m, m->flst, d->sc->obj);
	lst = m->flst;
	total = 0;
	while (++total && lst && (lst->id = total))
		lst = lst->n;
	m->total_file = total;
	m->menu.id = LOAD_OBJECT;
}


void			menu_object_btn_open(void *gen, void *mlx)
{
	t_gen	*d;
	t_mlx	*m;

	d = gen;
	m = mlx;
	if (!d->sc)
		ft_printf("pas de scene..\n");
	else
		menu_object_open_order(d, m);
}
