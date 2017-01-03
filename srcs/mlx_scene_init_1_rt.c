# include "raystruct.h"

// static void		set_switch(t_img *img, t_img *over)
// {
// 	img->mouse.over_id = 1;
//
// 	ft_memcpy(img, m->scene_img[1][img->mouse.over_id], sizeof(t_img));
// }

void			scene_init_1_rt(t_mlx *m, t_img *img)
{
	img = &m->scene_img[1][0];
	img->status = IMG_ANIM;
	img->anim.id = FADE_IN;
	img->anim.tempo = 6;
	img->pos[1] = m->winy - img->heigh - BTN_MARGIN;
	img->pos[0] = BTN_MARGIN;
	anim_init(img);
	// set_switch(img, 1);

}
