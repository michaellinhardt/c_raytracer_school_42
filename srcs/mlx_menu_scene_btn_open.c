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
		if (!m->flst)
			new->actif = 1;
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

void			menu_scene_open_order(t_gen *d, t_mlx *m)
{
	t_flst	*lst;
	int		total;
	char	*itoaa;

	menu_list_free(m, m->flst, (t_flst *)NULL);
	m->flst = NULL;
	build_list(m, m->flst, d->sc);
	lst = m->flst;
	total = 0;
	while (++total && lst && (lst->id = total))
		lst = lst->n;
	itoaa = ft_itoa(total - 1);
	notif2(m, N_NORMAL, itoaa, " scene loaded in the menu");
	ft_strdel(&itoaa);
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
		m->menu.next = LOAD_SCENE_ADD;
	else
		menu_scene_open_order(d, m);
}
