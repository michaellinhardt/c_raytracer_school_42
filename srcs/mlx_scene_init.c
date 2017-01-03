# include "raystruct.h"

void			anim_init(t_img *img)
{
	if (img->anim.id == FADE_IN)
		img->fade = 255;
	else if (img->anim.id == FADE_OUT)
		img->fade = 0;
}

void			scene_img_init(t_mlx *m, int i)
{
	if (m->scene == INTRO)
		scene_init_0_intro(m, (t_img *)NULL);
	else if (m->scene == RT)
		scene_init_1_rt(m, (t_img *)NULL);
	while (m->scene_img[m->scene][++i].img)
		if (m->scene_img[m->scene][i].status > IMG)
			anim_init(&m->scene_img[0][i]);
}
