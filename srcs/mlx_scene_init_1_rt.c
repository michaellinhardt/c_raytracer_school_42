# include "raytra_gen.h"
# include "raystruct.h"

static void		set_type_action(t_img *img, enum e_status status, int btn
	, void (*action)(void *ptr))
{
	img->status = status;
	img->mouse.btn = btn;
	img->mouse.action = action;
}

static void		set_area(t_img *img)
{
	img->mouse.top[0] = img->pos[0];
	img->mouse.top[1] = img->pos[1];
	img->mouse.bot[0] = img->pos[0] + img->width;
	img->mouse.bot[1] = img->pos[1] + img->heigh;
}

static void		set_over_click(t_mlx *m, t_img *img, int over, int click)
{
	if (over > 0)
	{
		img->mouse.over_id = over;
		m->scene_img[1][over].pos[0] = img->pos[0];
		m->scene_img[1][over].pos[1] = img->pos[1];
	}
	if (click > 0)
	{
		img->mouse.click_id = click;
		m->scene_img[1][click].pos[0] = img->pos[0];
		m->scene_img[1][click].pos[1] = img->pos[1];
	}
}

void			scene_init_1_rt_menu(t_mlx *m)
{
	anim_init(&m->scene_img[1][0], FADE_IN); // load btn
	anim_init(&m->scene_img[1][4], FADE_IN); // arrow left off
}

void			scene_init_1_rt(t_mlx *m, t_img *img)
{
	layer(m, 0, 2);
	layer(m, 1, 1);
	layer(m, 2, 1);
	layer(m, 3, 1);
	m->menu.draw = 1;

	img = &m->scene_img[1][0];
	img->pos[1] = m->winy - img->heigh - BTN_MARGIN;
	img->pos[0] = BTN_MARGIN;
	set_type_action(img, MENU, 1, &menu_load_btn_open);
	set_over_click(m, img, 1, 2);
	set_area(img);

	img = &m->scene_img[1][4];
	img->menu = LOAD_FILE;
	img->pos[0] = m->winx * 0.1;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	set_type_action(img, DISABLED, 1, NULL);
	set_over_click(m, img, 5, 6);
	set_area(img);

	img = &m->scene_img[1][7];
	img->menu = LOAD_FILE;
	img->pos[0] = m->winx * 0.95;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	set_type_action(img, DISABLED, 1, NULL);
	set_over_click(m, img, 8, 9);
	set_area(img);

	scene_init_1_rt_menu(m);
}
