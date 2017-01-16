#include "raytra_gen.h"
#include "raystruct.h"

void	scene_input_draw_cursor(t_mlx *m, t_get *g, t_img *lay)
{
	static int		cursor_frame = -1;

	if (m == NULL && g == NULL && lay == NULL)
	{
		cursor_frame = -1;
		return ;
	}
	if (m->input.key.left > 0 || m->input.key.right > 0)
		cursor_frame = -1;
	m->getcursor.pos[0] = g->box.pos[0]
	+ (g->i * INPUT_SIZE_CHAR_X) + INPUT_PADDING;
	m->getcursor.pos[1] = g->box.pos[1] + INPUT_PADDING + 1;
	if (++cursor_frame < INPUT_CURSOR_DISPLAY_UNDER)
		layer_add(m, lay, &m->getcursor);
	else if (cursor_frame == INPUT_CURSOR_FAME_TOTAL)
		cursor_frame = -1;
}
