#include "raytra_gen.h"
#include "raystruct.h"

void	scene_input(t_gen *d, t_mlx *m, int i)
{
	t_img	*lay;

	if (m->menu.draw == -1 || m->scene != RT)
		return ;
	lay = layer(m, 5, 1);
	while (++i < GET_APP_MAX)
	{
		if (m->get[i].menu != m->menu.id || !m->get[i].menu)
			continue ;
		else if (m->get[i].status == GET_FOCUS)
		{
			scene_input_action(d, m, &m->get[i], lay);
			scene_input_buff(d, m, &m->get[i], lay);
		}
		scene_input_draw_box(d, m, &m->get[i], lay);
		scene_input_draw_cursor(d, m, &m->get[i], lay);
	}
	(void)d;
}
