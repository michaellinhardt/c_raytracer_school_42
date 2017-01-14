#include "raytra_gen.h"
#include "raystruct.h"

static void		prepare_img(t_get *g, t_img *img)
{
	int		color;

	if (g->status == GET_DISABLED)
		color = INPUT_COLOR_DISABLED;
	else
		color = INPUT_COLOR_ENABLED;
	img->i = -1;
	while (++img->i < img->width * img->heigh)
		img->ptr[img->i] = color;
}

void	scene_input_draw_box(t_gen *d, t_mlx *m, t_get *g, t_img *lay)
{
	if (!g->box.img)
	{
		g->box.img = mlx_new_img(m, &g->box, g->box.width, g->box.heigh);
		g->box.fade = 255;
		prepare_img(g, &g->box);
	}
	layer_add(m, lay, &g->box);
	(void)d;
}
