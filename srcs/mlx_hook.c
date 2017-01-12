#include "raytra_gen.h"
#include "raystruct.h"

int		mouseo_hook(int x, int y, t_gen *d)
{
	if (d->sc && !d->sc->data)
		return (0);
	d->mlx.input.mouse.over_x = x;
	d->mlx.input.mouse.over_y = y;
	return (0);
}

int		keyr_hook(int key, t_gen *d)
{
	if (d->sc && !d->sc->data)
		return (0);
	if (key == 53)
		exit (0);
	else if (d->mlx.scene > INTRO)
	{
		if (key == 49 && (d->mlx.menu.draw *= -1))
		{
			if (d->mlx.menu.draw == 1)
			{
				layer(&d->mlx, 1, 1);
				scene_init_1_rt_menu(&d->mlx);
			}
		}
		(key == 123) ? d->mlx.input.key.left = 0 : 0;
		(key == 124) ? d->mlx.input.key.right = 0 : 0;
		(key == 125) ? d->mlx.input.key.down = 0 : 0;
		(key == 126) ? d->mlx.input.key.up = 0 : 0;
	}
	return (0);
}

int		keyp_hook(int key, t_gen *d)
{
	if (d->sc && !d->sc->data)
		return (0);
	(key == 123) ? d->mlx.input.key.left = 1 : 0;
	(key == 124) ? d->mlx.input.key.right = 1 : 0;
	(key == 125) ? d->mlx.input.key.down = 1 : 0;
	(key == 126) ? d->mlx.input.key.up = 1 : 0;
	return (0);
}

int		mousep_hook(int btn, int x, int y, t_gen *d)
{
	if (d->sc && !d->sc->data)
		return (0);
	(btn == 1) ? d->mlx.input.mouse.left = 1 : 0;
	(btn == 2) ? d->mlx.input.mouse.right = 1 : 0;
	return (0);
	(void)x;
	(void)y;
}

int		mouser_hook(int btn, int x, int y, t_gen *d)
{
	if (d->sc && !d->sc->data)
		return (0);
	(btn == 1) ? d->mlx.input.mouse.left = 0 : 0;
	(btn == 2) ? d->mlx.input.mouse.right = 0 : 0;
	d->mlx.input.mouse.release_x = x;
	d->mlx.input.mouse.release_y = y;
	mouse_release(d, btn, x, y);
	return (0);
}
