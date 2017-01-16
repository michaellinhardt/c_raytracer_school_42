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
		// 49 = espace
		if (key == 261 && (d->mlx.menu.draw *= -1))
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
		(key == 51) ? d->mlx.input.key.backspace = 0 : 0;
		(key == 117) ? d->mlx.input.key.suppr = 0 : 0;
		if (d->mlx.getfocus && (key == 123 || key == 124))
			cursor_move_left_right(&d->mlx, d->mlx.getfocus, 666);
		else if (d->mlx.getfocus && key == 51)
			input_delete_char(d->mlx.getfocus, d->mlx.getfocus->i - 1, 666);
		else if (d->mlx.getfocus && key == 117)
			input_delete_char(d->mlx.getfocus, d->mlx.getfocus->i, 666);
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
	(key == 51) ? d->mlx.input.key.backspace = 1 : 0;
	(key == 117) ? d->mlx.input.key.suppr = 1 : 0;
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
	ft_printf("coord: %d,%d\n", x, y);
	if (d->sc && !d->sc->data)
		return (0);
	(btn == 1) ? d->mlx.input.mouse.left = 0 : 0;
	(btn == 2) ? d->mlx.input.mouse.right = 0 : 0;
	d->mlx.input.mouse.release_x = x;
	d->mlx.input.mouse.release_y = y;
	if (d->mlx.getfocus && btn == 2 && (d->mlx.getfocus->action = GET_RESET)
	&& !(d->mlx.getfocus->i = 0))
		return (0);
	mouse_release(d, btn, x, y);
	return (0);
}
