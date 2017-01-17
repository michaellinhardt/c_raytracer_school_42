#include "raystruct.h"

// static void		purge_scene(t_gen *d, t_scene *sc, char *path, char nb)
// {
// 	t_scene		*prev;
// 	t_scene		*next;
//
// 	prev = (t_scene *)NULL;
// 	while (sc)
// 	{
// 		next = sc->next;
// 		if (sc->nb <= nb && !ft_strcmp(sc->path_save, path))
// 		{
// 			if (!prev && ((sc->next = d->sc_off) || 1))
// 			{
// 				d->sc_off = sc;
// 				d->sc = next;
// 				sc = next;
// 				continue ;
// 			}
// 			prev->next = next;
// 			sc->next = d->sc_off;
// 			d->sc_off = sc;
// 		}
// 		else if (sc->nb > nb)
// 			sc->path_save = ft_strdup(path);
// 		prev = sc;
// 		sc = next;
// 	}
// }
//
// void		menu_load_clic(t_gen *d, t_mlx *m, t_flst *elem)
// {
// 	char	*path;
// 	char	nb;
//
// 	if (!(nb = 0) && d->sc)
// 		nb = d->sc->nb;
// 	path = ft_strjoin(PATH_SCENE, elem->path);
// 	parse_scene(d, path);
// 	purge_scene(d, d->sc, path, nb);
// 	ft_strdel(&path);
// 	ft_strdel(&d->sc->data);
// 	(void)m;
// }

void			menu_scene_add_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (!m->menu.new_scene || !ft_strcmp(m->menu.new_scene
	, TXT_SCENE_ADD_NAME_DEFAUT))
		notif(m, N_WARNING, "you must enter a new scene name");
	else if (ft_strlen(m->menu.new_scene) < 3)
		notif(m, N_WARNING, "scene name must have at least 3 char");
	else
		notif(m, N_NORMAL, "loading new scene..");
	ft_printf("%s (%zu)\n", m->menu.new_scene, ft_strlen(m->menu.new_scene));
	(void)m;
	(void)gen;
	(void)mlx;
}
