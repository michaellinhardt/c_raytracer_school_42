#include "raytra_gen.h"

int		mouseo_hook(int x, int y, t_gen *d)
{
	if (d->mlx.scene == INTRO)
		return (0);
	d->mlx.input.mo_x = x;
	d->mlx.input.mo_y = y;
	return (0);
}

int		keyr_hook(int key, t_gen *d)
{
	if (key == 53)
		exit (0);
	else if (d->mlx.scene > INTRO)
	{
		(key == 123) ? d->mlx.input.left = 0 : 0;
		(key == 124) ? d->mlx.input.right = 0 : 0;
		(key == 125) ? d->mlx.input.down = 0 : 0;
		(key == 126) ? d->mlx.input.up = 0 : 0;
	}
	return (0);
}

int		keyp_hook(int key, t_gen *d)
{
	(key == 123) ? d->mlx.input.left = 1 : 0;
	(key == 124) ? d->mlx.input.right = 1 : 0;
	(key == 125) ? d->mlx.input.down = 1 : 0;
	(key == 126) ? d->mlx.input.up = 1 : 0;
	return (0);
}

int		mousep_hook(int btn, int x, int y, t_gen *d)
{
	(void)x;
	(void)y;
	(btn == 1) ? d->mlx.input.mleft = 1 : 0;
	(btn == 2) ? d->mlx.input.mright = 1 : 0;
	return (0);
}

int		mouser_hook(int btn, int x, int y, t_gen *d)
{
	(btn == 1) ? d->mlx.input.mleft = 0 : 0;
	(btn == 2) ? d->mlx.input.mright = 0 : 0;
	d->mlx.input.mr_x = x;
	d->mlx.input.mr_y = y;
	return (0);
}
