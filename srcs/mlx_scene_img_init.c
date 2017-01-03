# include "raystruct.h"

void			img_init(t_img *img)
{
	if (img->anim.id == FADE_IN)
		img->fade = 255;
}

void			scene_init_0_intro(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;
	img = &m->scene_img[0][0];
	img->status = IMG;
	// img = &m->scene_img[0][0];
	// img->mouse.bot[0] = m->winx;
	// img->mouse.bot[1] = m->winy;
	// img->mouse.btn = 3;
	// img->mouse.action = ;
	// img->anim.id = S0I0_ANIM_ID;
}

void			scene_img_init(t_mlx *m, int i)
{
	if (m->scene == INTRO)
		scene_init_0_intro(m, (t_img *)NULL);
	while (m->scene_img[m->scene][++i].img)
		img_init(&m->scene_img[0][i]);
}
