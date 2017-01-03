# include "raytra_gen.h"
# include "raystruct.h"

void			scene_init_1_rt(t_mlx *m, t_img *img)
{
	layer(m, 0, 2);
	img = &m->scene_img[1][0];
	img->status = IMG_ANIM;
	img->anim.id = FADE_IN;
	img->anim.tempo = 6;
	img->pos[1] = m->winy - img->heigh - BTN_MARGIN;
	img->pos[0] = BTN_MARGIN;
	img->mouse.over_id = 1;
	m->scene_img[1][1].pos[0] = img->pos[0];
	m->scene_img[1][1].pos[1] = img->pos[1];
	img->mouse.top[0] = img->pos[0];
	img->mouse.top[1] = img->pos[1];
	img->mouse.bot[0] = img->pos[0] + img->width;
	img->mouse.bot[1] = img->pos[1] + img->heigh;
	anim_init(img);
}
