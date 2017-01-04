# include "raytra_gen.h"
# include "raystruct.h"

void			scene_init_1_rt_menu(t_mlx *m)
{
	anim_init(&m->scene_img[1][0], FADE_IN);
}

void			scene_init_1_rt(t_mlx *m, t_img *img)
{
	layer(m, 0, 2);
	layer(m, 1, 1);
	layer(m, 2, 1);
	layer(m, 3, 1);
	m->menu.draw = 1;

	img = &m->scene_img[1][0];
	img->status = MENU;
	img->anim.tempo = 6;
	img->pos[1] = m->winy - img->heigh - BTN_MARGIN;
	img->pos[0] = BTN_MARGIN;
	img->mouse.btn = 1;
	img->mouse.action = &btn_load_menu;
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
	scene_init_1_rt_menu(m);
}
