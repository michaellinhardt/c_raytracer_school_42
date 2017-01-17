#include "raytra_gen.h"
#include "raystruct.h"

static void		purge_scene(t_gen *d, t_scene *sc, char *path, char nb)
{
	t_scene		*prev;
	t_scene		*next;

	prev = (t_scene *)NULL;
	while (sc)
	{
		next = sc->next;
		if (sc->path_save && sc->nb <= nb && !ft_strcmp(sc->path_save, path))
		{
			if (!prev && ((sc->next = d->sc_off) || 1))
			{
				d->sc_off = sc;
				d->sc = next;
				sc = next;
				continue ;
			}
			prev->next = next;
			sc->next = d->sc_off;
			d->sc_off = sc;
		}
		else if (sc->path_save && sc->nb > nb)
			sc->path_save = ft_strdup(path);
		prev = sc;
		sc = next;
	}
}

void		menu_load_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	char	*path;
	char	nb;

	if (!(nb = 0) && d->sc)
		nb = d->sc->nb;
	path = ft_strjoin(PATH_SCENE, elem->path);
	parse_scene(d, path);
	purge_scene(d, d->sc, path, nb);
	ft_strdel(&path);
	ft_strdel(&d->sc->data);
	(void)m;
}
