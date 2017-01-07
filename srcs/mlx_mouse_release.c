#include "raytra_gen.h"
#include "raystruct.h"

static void		purge_scene(t_gen *d, t_scene *sc, char *path, char nb)
{
	t_scene		*prev;
	t_scene		*next;

	prev = (t_scene *)NULL;
	next = (t_scene *)NULL;
	while (sc)
	{
		if (sc->nb <= nb && !ft_strcmp(sc->path_save, path))
		{
			if (!prev)
			{
				next = sc->next;
				sc->next = d->sc_off;
				d->sc_off = sc;
				d->sc = next;
				sc = next;
				continue ;
			}
			next = sc->next;
			prev->next = next;
			sc->next = d->sc_off;
			d->sc_off = sc;
			sc = next;
			continue ;
		}
		else if (sc->nb > nb)
			sc->path_save = ft_strdup(path);
		prev = sc;
		sc = sc->next;
	}
}

static int		load_clic(t_gen *d, t_flst *elem, int x, int y)
{
	int		i;
	t_img	*img;
	char	*path;
	char	nb;

	i = MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX;
	img = &d->mlx.scene_img[d->mlx.scene][MENU_LOAD_ID_IMG_PREVIEW_CLIC];
	nb = 0;
	if (d->sc)
		nb = d->sc->nb;
	while (elem && --i >= 0)
	{
		if (x >= elem->top[0] && x <= elem->bot[0] && y >= elem->top[1]
		&& y <= elem->bot[1])
		{
			img->pos[0] = elem->top[0];
			img->pos[1] = elem->top[1];
			layer_add(&d->mlx, layer(&d->mlx, 3, 0), img);
			path = ft_strjoin(PATH_SCENE, elem->path);
			parse_scene(d, path);
			purge_scene(d, d->sc, path, nb);
			ft_strdel(&path);
			// return (1);
		}
		elem = elem->n;
	}
	ft_printf("\n--------\n");
	ft_printf("scene actuellement dans la liste:\n");
	t_scene *sc;
	sc = d->sc;
	while (sc)
	{
		ft_printf("\t\t(%d) %s -> %s\n", sc->nb, sc->name, sc->path_save);
		sc = sc->next;
	}
	ft_printf("scene actuellement morte:\n");
	sc = d->sc_off;
	while (sc)
	{
		ft_printf("\t\t(%d) %s -> %s\n", sc->nb, sc->name, sc->path_save);
		sc = sc->next;
	}
	return (0);
}

void			mouse_release(t_gen *d, int btn, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
	if (d->mlx.scene == RT && d->mlx.menu.id == LOAD_FILE
	 && d->mlx.menu.draw == 1 && btn == 1 && load_clic(d, d->mlx.flst, x, y))
		return ;
	while (d->mlx.scene_img[d->mlx.scene][++i].img)
	{
		if ((img = &d->mlx.scene_img[d->mlx.scene][i])->status == MENU
		&& d->mlx.menu.draw == 1
		&& (d->mlx.menu.id == img->menu || img->menu == NONE)
		&& x >= img->mouse.top[0] && x <= img->mouse.bot[0]
		&& y >= img->mouse.top[1] && y <= img->mouse.bot[1]
		&& (btn == img->mouse.btn || img->mouse.btn == 3))
		{
			if (img->mouse.click_id > 0)
				layer_add(&d->mlx, layer(&d->mlx, 3, 0)
					, &d->mlx.scene_img[d->mlx.scene][img->mouse.click_id]);
			if (img->mouse.action)
				img->mouse.action((void *)&d->mlx);
			return ;
		}
	}
}
