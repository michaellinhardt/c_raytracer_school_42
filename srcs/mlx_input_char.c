#include "raytra_gen.h"
#include "raystruct.h"

static void		input_catch_char_string_file(t_get *g, char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '.' || c == '-' || c == '_')
	{
		g->action = GET_CHAR;
		g->c = c;
	}
}

static void		input_catch_char_double(t_get *g, char c)
{
	if (c == '.')
		c = ',';
	if (ft_isdigit(c) || c == ',')
	{
		g->action = GET_CHAR;
		g->c = c;
	}
}

static void		input_catch_char_int(t_get *g, char c)
{
	if (ft_isdigit(c) || (c == '-' && g->i == 0 && g->data[1] != '-'))
	{
		g->action = GET_CHAR;
		g->c = c;
	}
}

void			input_catch_char(t_gen *d, t_mlx *m, t_get *g, int key)
{
	char		c;

	if (key == 123 || key == 124)
		cursor_move_left_right(&d->mlx, m->getfocus, 666);
	else if (key == 51)
		input_delete_char(m->getfocus, m->getfocus->i - 1, 666);
	else if (key == 117)
		input_delete_char(m->getfocus, m->getfocus->i, 666);
	else if (key == 36)
		g->action = GET_VALID;
	else
	{
		g->c = '\0';
		if (!(c = mlx_keytochar(key)))
			return ;
		if (g->mode == MODE_DOUBLE)
			input_catch_char_double(g, c);
		if (g->mode == MODE_INT)
			input_catch_char_int(g, c);
		else if (g->mode == MODE_STRING)
			input_catch_char_string_file(g, c);
		else if (g->mode == MODE_STRING_FILE)
			input_catch_char_string_file(g, c);

	}
}
