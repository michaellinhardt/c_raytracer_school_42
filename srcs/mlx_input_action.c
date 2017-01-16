#include "raytra_gen.h"
#include "raystruct.h"

int				cursor_move_left_right(t_mlx *m, t_get *g, int ret)
{
	static int		move_speed = -1;

	if (move_speed == INPUT_CURSOR_MOVE_TEMPO || ret == 666)
		move_speed = -1;
	if (ret == 666 || ++move_speed)
		return (1);
	if (m->input.key.left > 0 && g->i > 0 && ++ret)
	{
		g->i--;
	}
	else if (m->input.key.right > 0 && g->i < (int)ft_strlen(g->data)
	&& g->i < g->size_max && ++ret)
	{
		g->i++;
	}
	return (ret);
}

void			scene_input_action(t_gen *d, t_mlx *m, t_get *g, t_img *lay)
{
	if ((m->input.key.left > 0 || m->input.key.right > 0)
	&& cursor_move_left_right(m, g, 0))
		return ;
	(void)d;
	(void)m;
	(void)lay;
	(void)g;
}
