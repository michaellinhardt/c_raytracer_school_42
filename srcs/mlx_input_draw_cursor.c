#include "raytra_gen.h"
#include "raystruct.h"

void	scene_input_draw_cursor(t_mlx *m, t_get *g, t_img *lay)
{
	static int		cursor_frame = -1;

	if (++cursor_frame == 0 && ft_printf("fade = 0\n"))
		while (++m->getcursor.i < m->getcursor.width * m->getcursor.heigh)
			m->getcursor.ptr[m->getcursor.i] = (unsigned)INPUT_CURSOR_COLOR;
	else if (cursor_frame == INPUT_CURSOR_DISPLAY_AT && ft_printf("fade = 255\n"))
		while (++m->getcursor.i < m->getcursor.width * m->getcursor.heigh)
			m->getcursor.ptr[m->getcursor.i] = 0xFF000000;
	else if (cursor_frame == INPUT_CURSOR_FAME_TOTAL)
		cursor_frame = -1;
	m->getcursor.pos[0] = g->box.pos[0]
	+ (g->i * INPUT_SIZE_CHAR_X) + INPUT_PADDING;
	m->getcursor.pos[1] = g->box.pos[1] + INPUT_PADDING + 1;
	layer_add(m, lay, &m->getcursor);
}
