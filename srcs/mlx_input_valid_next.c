#include "raytra_gen.h"
#include "raystruct.h"

void		input_valid_string(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	ft_strdel(&(*g->target.ptr_str));
	*g->target.ptr_str = ft_strdup(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

void		input_valid_double(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	*g->target.ptr_double = ft_atob(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

void		input_valid_double_but_int(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	*g->target.ptr_double = ft_atob(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

void		input_valid_int(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	*g->target.ptr_int = ft_atoi(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}
