# include "raytra_gen.h"
# include "raystruct.h"

void			set_type_action(t_img *img, enum e_status status, int btn
			, void (*action)(void *ptr))
{
	img->status = status;
	img->mouse.btn = btn;
	img->mouse.action = action;
}

void			set_area(t_img *img)
{
	img->mouse.top[0] = img->pos[0];
	img->mouse.top[1] = img->pos[1];
	img->mouse.bot[0] = img->pos[0] + img->width;
	img->mouse.bot[1] = img->pos[1] + img->heigh;
}

void			set_over_click(t_mlx *m, t_img *img, int over, int click)
{
	if (over > 0)
	{
		img->mouse.over_id = over;
		m->scene_img[1][over].pos[0] = img->pos[0];
		m->scene_img[1][over].pos[1] = img->pos[1];
		m->scene_img[1][over].set_alpha = img->set_alpha;
		m->scene_img[1][over].fade_min = img->fade_min;
		m->scene_img[1][over].fade_max = img->fade_max;
	}
	if (click > 0)
	{
		img->mouse.click_id = click;
		m->scene_img[1][click].pos[0] = img->pos[0];
		m->scene_img[1][click].pos[1] = img->pos[1];
		m->scene_img[1][click].set_alpha = img->set_alpha;
		m->scene_img[1][click].fade_min = img->fade_min;
		m->scene_img[1][click].fade_max = img->fade_max;
	}
}

/*
** 	anim_init(&m->scene_img[1][0], FADE_IN); // load btn
*/
void			scene_init_1_rt_menu(t_mlx *m)
{
	anim_init(&m->scene_img[1][ID_IMG_MENU_CADRE], FADE_IN);
	anim_init(&m->scene_img[1][ID_IMG_MENU_CADRE_LIGHTNING], FADE_IN);
	anim_init(&m->scene_img[1][ID_IMG_MENU_CADRE_LOGO], FADE_IN);
	// anim_init(&m->scene_img[1][14], FADE_IN);
	// anim_init(&m->scene_img[1][17], FADE_IN);
	// anim_init(&m->scene_img[1][4], FADE_IN);
	// anim_init(&m->scene_img[1][7], FADE_IN);
}

void			scene_init_1_rt(t_mlx *m, t_img *img)
{
	layer(m, 0, 2);
	layer(m, 1, 1);
	layer(m, 2, 1);
	layer(m, 3, 1);
	img = layer(m, 4, 2);
	img->i = -4;
	while ((img->i += 4) < (img->sl * m->winy))
			img->str[img->i + 3] = (unsigned char)50;
	scene_init_1_rt_img(m, img);
	scene_init_1_rt_menu(m);
	m->menu.draw = 1;
	menu_load_btn_open((void *)m);
}
