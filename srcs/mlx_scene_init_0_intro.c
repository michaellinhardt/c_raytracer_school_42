#include "raystruct.h"

void			scene_init_0_intro(t_mlx *m, t_img *img)
{
	img = &m->scene_img[0][0];
	img->status = MENU;
	img->anim.id = FADE_IN;
	img->anim.tempo = 5;
	img->mouse.bot[0] = m->winx;
	img->mouse.bot[1] = m->winy;
	img->mouse.btn = 3;
	img->mouse.action = &scene_0_skip;
	m->menu.draw = 1;
	anim_init(img, FADE_IN);
}
