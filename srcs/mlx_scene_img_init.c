# include "raystruct.h"

void			anim_init(t_img *img)
{
	if (img->anim.id == FADE_IN)
		img->fade = 255;
}

void			scene_init_0_intro(t_mlx *m, t_img *img)
{
	img = &m->scene_img[0][0];
	img->status = OBJECT;
	img->anim.id = FADE_IN;
	img->anim.tempo = 1;
	img->mouse.bot[0] = m->winx;
	img->mouse.bot[1] = m->winy;
}

void			scene_img_init(t_mlx *m, int i)
{
	if (m->scene == INTRO)
		scene_init_0_intro(m, (t_img *)NULL);
	while (m->scene_img[m->scene][++i].img)
		if (m->scene_img[m->scene][++i].status > IMG)
			anim_init(&m->scene_img[0][i]);
}
