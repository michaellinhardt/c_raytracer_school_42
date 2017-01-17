#include "raytra_gen.h"
#include "raystruct.h"

static void		input_valid_string(t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	ft_strdel(&(*g->target.ptr_str));
	*g->target.ptr_str = ft_strdup(g->data);
	input_set_focus(m, (t_get *)NULL, -1, -1);
}

void			input_valid(t_gen *d, t_mlx *m, t_get *g)
{
	if (g->mode == MODE_STRING_FILE)
		input_valid_string(m, g);
	if (g->send)
		g->send(d, m);
	(void)m;
}