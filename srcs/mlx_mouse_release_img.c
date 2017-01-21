#include "raytra_gen.h"
#include "raystruct.h"

static void		set_obj_type(t_mlx *m, int i)
{
	if (i == IB_OBJECT_MOD_TYPE1)
	m->menu.obj_type = SPHERE;
	if (i == IB_OBJECT_MOD_TYPE2)
	m->menu.obj_type = RECTANGLE;
	if (i == IB_OBJECT_MOD_TYPE3)
	m->menu.obj_type = PLAN;
	if (i == IB_OBJECT_MOD_TYPE4)
	m->menu.obj_type = CONE;
	if (i == IB_OBJECT_MOD_TYPE5)
	m->menu.obj_type = CYLINDRE;
	if (i == IB_OBJECT_MOD_TYPE6)
	m->menu.obj_type = COMPLEXE;
	if (i == IB_OBJECT_MOD_TYPE7)
	m->menu.obj_type = BOLOID;
	if (i == IB_OBJECT_MOD_TYPE8)
	m->menu.obj_type = TRIANGLE;
	if (i == IB_OBJECT_MOD_TYPE9)
	m->menu.obj_type = ELLIPSE;
}

int				mouse_release_img(t_gen *d, int btn, int x, int y)
{
	t_img		*img;
	int			i;

	i = -1;
	while (d->mlx.scene_img[d->mlx.scene][++i].img)
		if (area((img = &d->mlx.scene_img[d->mlx.scene][i]), NULL, x, y)
		&& img->status == MENU && d->mlx.menu.draw == 1
		&& (d->mlx.menu.id == img->menu || img->menu == NONE)
		&& (btn == img->mouse.btn || img->mouse.btn == 3))
		{
			if (img->mouse.click_id > 0)
				layer_add(&d->mlx, layer(&d->mlx, 3, 0)
					, &d->mlx.scene_img[d->mlx.scene][img->mouse.click_id]);
			if (i >= IB_OBJECT_MOD_TYPE1 && i <= IB_OBJECT_MOD_TYPE9)
				set_obj_type(&d->mlx, i);
			if (img->mouse.action)
				img->mouse.action((void *)d, (void *)&d->mlx);
			return (1);
		}
	return (0);
}
