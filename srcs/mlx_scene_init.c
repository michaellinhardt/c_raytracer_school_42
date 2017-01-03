# include "raystruct.h"

void			scene_img_init_scene(t_mlx *m, t_img *img, int i)
{
	(void)m;
	(void)img;
	(void)i;
	// while (m->scene_img[m->scene][++i].img)
	// {
	// 	img = &m->scene_img[0][i];
	// 	if (img->anim.id == FADE_IN)
	// 		img->fade = 255;
	// }
}

void			scene_img_init_0_intro(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;
	// img = &m->scene_img[0][0];
	// img->mouse.bot[0] = m->winx;
	// img->mouse.bot[1] = m->winy;
	// img->mouse.btn = 3;
	// img->mouse.action = ;
	// img->anim.id = S0I0_ANIM_ID;
}

void			scene_img_init(t_mlx *m)
{
	if (m->scene == INTRO)
		scene_img_init_0_intro(m, (t_img *)NULL);
	scene_img_init_scene(m, (t_img *)NULL, -1);
}
