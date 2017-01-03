#include "raystruct.h"

void			scene_1_rt(t_mlx *m)
{
	layer(m, 2, 1);
	mouse_over(m, m->input.mouse.over_x, m->input.mouse.over_y);
	itow(m, layer(m, 0, 0)->img, 0, 0);
	itow(m, layer(m, 1, 0)->img, 0, 0);
	itow(m, layer(m, 2, 0)->img, 0, 0);
}
