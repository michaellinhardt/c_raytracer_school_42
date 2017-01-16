#include "raystruct.h"

static void		push_text(t_mlx *m, char *str, t_get *g, unsigned color)
{
	static int		middle_line = (INPUT_SIZE_CHAR_Y - INPUT_PADDING) / 2 - 1;

	if (!str)
		return ;
	mlx_string_put(m->mlx, m->win, g->box.pos[0] + INPUT_PADDING
		, g->box.pos[1] + middle_line, color, str);
}

static void		text_from_target(t_mlx *m, t_get *g, unsigned color)
{
	char			*tmp;

	tmp = NULL;
	if ((tmp = input_target_to_str(g)))
		push_text(m, tmp, g, color);
	ft_strdel(&tmp);
}

void			scene_text_input(t_mlx *m, t_get *g, int i)
{
	unsigned	color;

	while (++i < GET_APP_MAX && (g = &m->get[i]))
		if (g->menu > NONE && g->menu == m->menu.id)
		{
			color = INPUT_TEXT_COLOR;
			if (g->status == GET_FOCUS)
				color = INPUT_TEXT_COLOR_FOCUS;
			else if (g->status == GET_DISABLED)
				color = INPUT_TEXT_COLOR_DISABLED;
			if (g->status != GET_FOCUS)
				text_from_target(m, g, color);
			else
				push_text(m, g->data, g, color);
		}
}
