#include "raytra_gen.h"
#include "raystruct.h"

static void		input_catch_char_string_file(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (ft_isdigit(c) || ft_isalpha(c) || c == '.' || c == '-' || c == '_')
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
}

static void		input_catch_char_double(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (c == '.')
		c = ',';
	if (ft_isdigit(c) || c == ',')
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
	(void)m;
}

static void		input_catch_char_int(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (ft_isdigit(c) || (c == '-' && g->i == 0 && g->data[1] != '-'))
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
	(void)m;
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
		{
			notif(m, N_WARNING, "this char isnt allowed in this app");
			return ;
		}
		if (g->mode == MODE_DOUBLE)
			input_catch_char_double(m, g, c);
		if (g->mode == MODE_INT)
			input_catch_char_int(m, g, c);
		else if (g->mode == MODE_STRING)
			input_catch_char_string_file(m, g, c);
		else if (g->mode == MODE_STRING_FILE)
			input_catch_char_string_file(m, g, c);

	}
}