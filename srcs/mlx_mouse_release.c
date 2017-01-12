#include "raytra_gen.h"
#include "raystruct.h"

static void		call_clic(t_gen *d, t_mlx *m, t_flst *elem, enum e_menu menu)
{
	if (menu == LOAD_FILE)
		menu_load_clic(d, m, elem);
	else if (menu == LOAD_SCENE)
		menu_scene_clic(d, m, elem);
	else if (menu == LOAD_OBJECT)
		menu_object_clic(d, m, elem);
	else if (menu == LOAD_SPOT)
		menu_spot_clic(d, m, elem);
}

static int		load_clic(t_gen *d, t_flst *elem, int x, int y)
{
	int		i;
	t_img	*img;

	i = MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX;
	img = &d->mlx.scene_img[d->mlx.scene][ID_IMG_PREVIEW_CLIC];
	while (elem && --i >= 0)
	{
		if (area(NULL, elem, x, y))
		{
			img->pos[0] = elem->top[0];
			img->pos[1] = elem->top[1];
			layer_add(&d->mlx, layer(&d->mlx, 3, (d->mlx.menu.draw *= -1)), img);
			call_clic(d, &d->mlx, elem, d->mlx.menu.id);
			return (1);
		}
		elem = elem->n;
	}
	return (0);
}

void			mouse_release(t_gen *d, int btn, int x, int y)
{
	int		i;
	t_img	*img;

	i = -1;
	if (d->mlx.scene == RT && d->mlx.flst
	&& (d->mlx.menu.id >= LOAD_FILE || d->mlx.menu.id <= LOAD_SPOT)
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
				img->mouse.action((void *)d, (void *)&d->mlx);
			return ;
		}
	}
}
