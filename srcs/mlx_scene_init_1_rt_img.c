# include "raytra_gen.h"
# include "raystruct.h"

void			scene_init_1_rt_img(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;

	img = &m->scene_img[1][ID_IMG_MENU_CADRE];
	img->fade_min = 180;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_MENU_CADRE_LIGHTNING];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = 4;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_MENU_CADRE_LOGO];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = 22;
	img->fade_min = 100;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_LOAD];
	img->pos[0] = 530;
	img->pos[1] = 11;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_load_btn_open);
	set_over_click(m, img, ID_IMG_BTN_LOAD_OVER, ID_IMG_BTN_LOAD_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_SAVE];
	img->pos[0] = 1095;
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_LOAD].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_save_btn_open);
	set_over_click(m, img, ID_IMG_BTN_SAVE_OVER, ID_IMG_BTN_SAVE_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_SCENE];
	img->pos[0] = 677;
	img->pos[1] = 965;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_btn_open);
	set_over_click(m, img, ID_IMG_BTN_SCENE_OVER, ID_IMG_BTN_SCENE_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_OBJECT];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0]
	+ (img->width * 1) + (BOT_BTN_X_DECALLAGE * 1);
	img->pos[1] = 965;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_object_btn_open);
	set_over_click(m, img, ID_IMG_BTN_OBJECT_OVER, ID_IMG_BTN_OBJECT_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_SPOT];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0]
	+ (img->width * 2) + (BOT_BTN_X_DECALLAGE * 2);
	img->pos[1] = 965;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_spot_btn_open);
	set_over_click(m, img, ID_IMG_BTN_SPOT_OVER, ID_IMG_BTN_SPOT_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_CAMERA];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0]
	+ (img->width * 3) + (BOT_BTN_X_DECALLAGE * 3);
	img->pos[1] = 965;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 0, NULL);
	set_over_click(m, img, ID_IMG_BTN_CAMERA_OVER, ID_IMG_BTN_CAMERA_CLICK);

}
