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
		if (sc->nb <= nb && !ft_strcmp(sc->path_save, path))
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
		else if (sc->nb > nb)
			sc->path_save = ft_strdup(path);
		prev = sc;
		sc = next;
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
	if (!(nb = 0) && d->sc)
		nb = d->sc->nb;
	while (elem && --i >= 0)
	{
		if (area(NULL, elem, x, y) && (d->mlx.draw_rt = 1))
		{
			img->pos[0] = elem->top[0];
			img->pos[1] = elem->top[1];
			layer_add(&d->mlx, layer(&d->mlx, 3, (d->mlx.menu.draw = 0)), img);
			path = ft_strjoin(PATH_SCENE, elem->path);
			parse_scene(d, path);
			purge_scene(d, d->sc, path, nb);
			ft_strdel(&path);
			return (1);
		}
		elem = elem->n;
	}
	return (0);
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
		&& d->mlx.menu.draw == 1 && area(img, NULL, x, y)
		&& (d->mlx.menu.id == img->menu || img->menu == NONE)
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
