#include "raystruct.h"

static void		load_preview(t_mlx *m, t_flst *elem)
{
	(void)m;
	(void)elem;
}

static void		build_list(t_mlx *m, t_flst *new, t_scene *sc)
{
	while (sc)
	{
		if (!(new = (t_flst *)ft_memalloc(sizeof(t_flst))))
			error(2, "malloc t_flst struct");
		if (sc->name)
			new->path = ft_strdup(sc->name);
		else
			new->path = ft_strdup("Unknow..");
		if (!m->flst && (m->flst = new) && (!(new->p = (t_flst *)NULL)))
				new->n = (t_flst *)NULL;
		else if ((m->flst->p = new)
		&& (new->n = m->flst)
		&& (!(new->p = NULL)))
			m->flst = new;
		m->flst->scene = sc;
		load_preview(m, m->flst);
		sc = sc->next;
	}
}

static void		menu_scene_open_order(t_gen *d, t_mlx *m)
{
	t_flst	*lst;
	int		total;

	menu_list_free(m, m->flst, (t_flst *)NULL);
	m->flst = NULL;
	build_list(m, m->flst, d->sc);
	lst = m->flst;
	total = 0;
	while (++total && lst && (lst->id = total))
		lst = lst->n;
	m->total_file = total;
	m->menu.id = LOAD_SCENE;
}


void			menu_scene_btn_open(void *gen, void *mlx)
{
	t_gen	*d;
	t_mlx	*m;

	d = gen;
	m = mlx;
	if (!d->sc)
		ft_printf("scene btn new\n");
	else
		menu_scene_open_order(d, m);
}
