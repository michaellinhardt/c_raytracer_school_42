#include "raytra_gen.h"
#include "raystruct.h"

int			mouse_release_img(t_gen *d, int btn, int x, int y)
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
			if (img->mouse.action)
				img->mouse.action((void *)d, (void *)&d->mlx);
			return (1);
		}
	return (0);
}
