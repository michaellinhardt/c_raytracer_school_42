#include "raytra_gen.h"
#include "raystruct.h"

void			input_catch_char(t_gen *d, t_mlx *m, t_get *g, int key)
{
	char		c;

	ft_printf("key: %d\n", key);

	if (key == 123 || key == 124)
		cursor_move_left_right(&d->mlx, m->getfocus, 666);
	else if (key == 51)
		input_delete_char(m->getfocus, m->getfocus->i - 1, 666);
	else if (key == 117)
		input_delete_char(m->getfocus, m->getfocus->i, 666);
	else if (key == 36 || key == 76)
		g->action = GET_VALID;
	else
	{
		g->c = '\0';
		if (!(c = mlx_keytochar(key)))
		{
			notif(m, N_WARNING, "this char isnt allowed in this app");
			return ;
		}
		input_catch_char_end(m, g, c);
	}
}
