# include "raytra_gen.h"
# include "raystruct.h"

void			scene_init_1_rt_img(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;
	// // LOAD BTN
	// img = &m->scene_img[1][0];
	// img->pos[0] = BTN_MARGIN;
	// img->pos[1] = m->winy - img->heigh - BTN_MARGIN;
	// set_type_action(img, MENU, 1, &menu_load_btn_open);
	// set_over_click(m, img, 1, 2);
	// set_area(img);
	//
	// // SAVE BTN
	// img = &m->scene_img[1][14];
	// img->pos[0] = m->scene_img[1][0].pos[0];
	// img->pos[1] = m->scene_img[1][0].pos[1] - BTN_MARGIN - img->heigh;
	// set_type_action(img, MENU, 1, &menu_save_btn_open);
	// set_over_click(m, img, 15, 16);
	// set_area(img);
	//
	// // SPOT BTN
	// img = &m->scene_img[1][17];
	// img->pos[0] = m->scene_img[1][14].pos[0];
	// img->pos[1] = m->scene_img[1][14].pos[1] - BTN_MARGIN - img->heigh;
	// set_type_action(img, MENU, 1, &menu_spot_btn_open);
	// set_over_click(m, img, 18, 19);
	// set_area(img);
	//
	// // OBJECT BTN
	// img = &m->scene_img[1][20];
	// img->pos[0] = m->scene_img[1][17].pos[0];
	// img->pos[1] = m->scene_img[1][17].pos[1] - BTN_MARGIN - img->heigh;
	// set_type_action(img, MENU, 1, &menu_object_btn_open);
	// set_over_click(m, img, 21, 22);
	// set_area(img);
	//
	// img = &m->scene_img[1][4];
	// img->menu = LOAD_FILE;
	// img->pos[0] = m->winx * 0.1;
	// img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	// set_type_action(img, DISABLED, 1, &menu_load_btn_prev);
	// set_over_click(m, img, 5, 6);
	// set_area(img);
	//
	// img = &m->scene_img[1][7];
	// img->menu = LOAD_FILE;
	// img->pos[0] = m->winx * 0.95;
	// img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	// set_type_action(img, DISABLED, 1, &menu_load_btn_next);
	// set_over_click(m, img, 8, 9);
	// set_area(img);
}
