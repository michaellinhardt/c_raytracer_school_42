#include "raytra_gen.h"
#include "raystruct.h"

void			cursor_move_left_right(t_mlx *m, t_get *g, int reset)
{
	static int		move_speed = -1;

	if (move_speed == INPUT_CURSOR_MOVE_TEMPO || reset > 0)
		move_speed = -1;
	if (reset > 0 || ++move_speed)
		return ;
	if (m->input.key.left > 0 && g->i > 0)
		g->i--;
	else if (m->input.key.right > 0 && g->i < (int)ft_strlen(g->data)
	&& g->i < g->size_max)
		g->i++;
	return ;
}

void			input_delete_char(t_get *g, int pos, int reset)
{
	static int		move_speed = -1;
	int				i;
	int				j;

	if (move_speed == INPUT_CURSOR_DEL_TEMPO || reset > 0)
		move_speed = -1;
	if (reset > 0 || ++move_speed)
		return ;
	i = -1;
	j = -1;
	while (g->data[++i])
		if (i != pos)
			g->tmp[++j] = g->data[i];
	g->tmp[++j] = '\0';
	ft_memcpy(g->data, g->tmp, j + 1);
	if (g->i > 0 && pos < g->i)
		g->i--;
}

static void		input_add_char(t_get *g, int i, int j)
{
	int		copied;

	if (g->i == g->size_max - 1 || g->i == GET_SIZE_MAX - 1)
		return ;
	copied = 0;
	while (g->data[++i])
		if (g->i == i && copied == 0 && ++copied)
		{
			g->tmp[++j] = g->c;
			g->tmp[++j] = g->data[i];
		}
		else
			g->tmp[++j] = g->data[i];
	if (g->i == i && copied == 0)
		g->tmp[++j] = g->c;
	g->i++;
	g->tmp[++j] = '\0';
	ft_memcpy(g->data, g->tmp, j + 1);
	(void)i;
	(void)j;
}

void			scene_input_action(t_gen *d, t_mlx *m, t_get *g, t_img *lay)
{
	if (m->input.key.left > 0 || m->input.key.right > 0)
		cursor_move_left_right(m, g, 0);
	else if (m->input.key.suppr > 0 && g->i <= (int)ft_strlen(g->data)
	&& g->i < g->size_max)
		input_delete_char(g, g->i, 0);
	else if (m->input.key.backspace > 0 && g->i > 0)
		input_delete_char(g, g->i - 1, 0);
	else if (g->action == GET_RESET && !(g->action = GET_WAITING))
		g->data[0] = '\0';
	else if (g->action == GET_CHAR && !(g->action = GET_WAITING))
		input_add_char(g, -1, -1);
	else if (g->action == GET_VALID && !(g->action = GET_WAITING))
		input_valid(m, g);
	(void)d;
	(void)lay;
}
