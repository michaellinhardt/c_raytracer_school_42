#include "raytra_gen.h"
#include "raystruct.h"

static void		set_fade(t_get *g)
{
	if (g->status == GET_FOCUS)
		g->fade_focus = (g->fade_focus
		+ INPUT_BORDER_FADE_SPEED) > 255 ? 255 : (g->fade_focus
		+ INPUT_BORDER_FADE_SPEED);
	else
		g->fade_focus = (g->fade_focus
		- INPUT_BORDER_FADE_SPEED) < 0 ? 0 : (g->fade_focus
		- INPUT_BORDER_FADE_SPEED);

}

void			scene_input(t_gen *d, t_mlx *m, int i)
{
	t_img	*lay;

	if (m->menu.draw == -1 || m->scene != RT)
		return ;
	lay = layer(m, 5, 1);
	while (++i < GET_APP_MAX)
	{
		if (m->get[i].menu != m->menu.id || m->get[i].menu == NONE)
			continue ;
		set_fade(&m->get[i]);
		if (m->get[i].status == GET_FOCUS)
		{
			scene_input_action(d, m, &m->get[i], lay);
			scene_input_buff(d, m, &m->get[i], lay);
		}
		scene_input_draw_box(d, m, &m->get[i], lay);
		scene_input_draw_cursor(d, m, &m->get[i], lay);
	}
	(void)d;
}
