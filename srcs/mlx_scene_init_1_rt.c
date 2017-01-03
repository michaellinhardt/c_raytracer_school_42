# include "raytra_gen.h"
# include "raystruct.h"

void			scene_init_1_rt(t_mlx *m, t_img *img)
{
	layer(m, 0, 2);
	layer(m, 1, 1);
	layer(m, 2, 1);
	layer(m, 3, 1);
	img = &m->scene_img[1][0];
	img->status = OBJECT;
	img->anim.id = FADE_IN;
	img->anim.tempo = 6;
	img->pos[1] = m->winy - img->heigh - BTN_MARGIN;
	img->pos[0] = BTN_MARGIN;
	img->mouse.btn = 1;
	img->mouse.action = NULL;
	img->mouse.over_id = 1;
	img->mouse.click_id = 2;
	m->scene_img[1][1].pos[0] = img->pos[0];
	m->scene_img[1][1].pos[1] = img->pos[1];
	m->scene_img[1][2].pos[0] = img->pos[0];
	m->scene_img[1][2].pos[1] = img->pos[1];
	img->mouse.top[0] = img->pos[0];
	img->mouse.top[1] = img->pos[1];
	img->mouse.bot[0] = img->pos[0] + img->width;
	img->mouse.bot[1] = img->pos[1] + img->heigh;
	anim_init(img);
}
