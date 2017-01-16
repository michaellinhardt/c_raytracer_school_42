#include "raytra_gen.h"
#include "raystruct.h"

static void		input_catch_char_string_file(t_get *g, char c)
{
	g->c = '\0';
	if (!c)
		return ;
	if (ft_isdigit(c) || ft_isalpha(c) || c == '.' || c == '-' || c == '_')
	{
		g->action = GET_CHAR;
		g->c = c;
	}
}

void			input_catch_char(t_gen *d, t_mlx *m, t_get *g, int key)
{
	if (key == 123 || key == 124)
		cursor_move_left_right(&d->mlx, m->getfocus, 666);
	else if (key == 51)
		input_delete_char(m->getfocus, m->getfocus->i - 1, 666);
	else if (key == 117)
		input_delete_char(m->getfocus, m->getfocus->i, 666);
	else if (g->mode == MODE_STRING_FILE)
		input_catch_char_string_file(g, mlx_keytochar(key));
}
