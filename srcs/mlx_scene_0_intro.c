#include "raystruct.h"

void			scene_0_intro(t_mlx *m)
{
	itow(m, layer(m, 0, 0)->img, 0, 0);
	itow(m, layer(m, 1, 0)->img, 0, 0);
	if (m->scene_img[0][0].fade == 255
	&& m->scene_img[0][0].anim.id == STATIC)
		m->scene++;
}

void			scene_0_skip(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->scene_img[0][0].anim.id != FADE_OUT)
	{
		m->scene_img[0][0].anim.id = FADE_OUT;
		m->scene_img[0][0].anim.tempo = 7;
	}
	(void)gen;
	(void)mlx;
}
