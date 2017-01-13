# include "raytra_gen.h"
# include "raystruct.h"

void			scene_init_1_rt_img(t_mlx *m, t_img *img)
{
	(void)m;
	(void)img;

	img = &m->scene_img[1][ID_IMG_MENU_CADRE];
	img->fade_min = 110;
	img->set_alpha = 0xFF000000;
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
	img->pos[1] = 960;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_btn_open);
	set_over_click(m, img, ID_IMG_BTN_SCENE_OVER, ID_IMG_BTN_SCENE_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_OBJECT];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0]
	+ (img->width * 1) + (BOT_BTN_X_DECALLAGE * 1);
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_object_btn_open);
	set_over_click(m, img, ID_IMG_BTN_OBJECT_OVER, ID_IMG_BTN_OBJECT_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_SPOT];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0]
	+ (img->width * 2) + (BOT_BTN_X_DECALLAGE * 2);
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_spot_btn_open);
	set_over_click(m, img, ID_IMG_BTN_SPOT_OVER, ID_IMG_BTN_SPOT_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_CAMERA];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0]
	+ (img->width * 3) + (BOT_BTN_X_DECALLAGE * 3);
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_camera_btn_open);
	set_over_click(m, img, ID_IMG_BTN_CAMERA_OVER, ID_IMG_BTN_CAMERA_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_ARROW_LEFT_OFF];
	img->pos[0] = 8;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_ARROW_LEFT];
	img->menu = LOAD_FILE;
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_ARROW_LEFT_OFF].pos[0];
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_ARROW_LEFT_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_btn_left);
	set_over_click(m, img
		, ID_IMG_BTN_ARROW_LEFT_OVER, ID_IMG_BTN_ARROW_LEFT_CLICK);

	img = &m->scene_img[1][ID_IMG_BTN_ARROW_RIGHT_OFF];
	img->pos[0] = m->winx - img->width - 8;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_ARROW_RIGHT];
	img->menu = LOAD_FILE;
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_ARROW_RIGHT_OFF].pos[0];
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_ARROW_RIGHT_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_btn_right);
	set_over_click(m, img
		, ID_IMG_BTN_ARROW_RIGHT_OVER, ID_IMG_BTN_ARROW_RIGHT_CLICK);

	img = &m->scene_img[1][ID_IMG_PREVIEW_NO_IMG];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);

	img = &m->scene_img[1][ID_IMG_PREVIEW];
	img->fade_min = 100;
	img->set_alpha = -1;
	layer_set_alpha(img);

	img = &m->scene_img[1][ID_IMG_PREVIEW_OVER];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);

	img = &m->scene_img[1][ID_IMG_PREVIEW_CLIC];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);


	// BOUTON OFF
	img = &m->scene_img[1][ID_IMG_BTN_SCENE_OFF];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[0];
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_SCENE].pos[1];
	img->fade_min = m->scene_img[1][ID_IMG_BTN_SCENE].fade_min;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 0, NULL);


	img = &m->scene_img[1][ID_IMG_BTN_OBJECT_OFF];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_OBJECT].pos[0];
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_OBJECT].pos[1];
	img->fade_min = m->scene_img[1][ID_IMG_BTN_OBJECT].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_SPOT_OFF];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_SPOT].pos[0];
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_SPOT].pos[1];
	img->fade_min = m->scene_img[1][ID_IMG_BTN_SPOT].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_CAMERA_OFF];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_CAMERA].pos[0];
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_CAMERA].pos[1];
	img->fade_min = m->scene_img[1][ID_IMG_BTN_CAMERA].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_EDIT_ADD_OFF];
	img->pos[0] = 183;
	img->pos[1] = 952;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_EDIT_MOD_OFF];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_EDIT_ADD_OFF].pos[0]
	+ (img->width * 1) + (BOT_BTN_X_DECALLAGE * 1);
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_EDIT_ADD_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][ID_IMG_BTN_EDIT_DEL_OFF];
	img->pos[0] = m->scene_img[1][ID_IMG_BTN_EDIT_ADD_OFF].pos[0]
	+ (img->width * 2) + (BOT_BTN_X_DECALLAGE * 2);
	img->pos[1] = m->scene_img[1][ID_IMG_BTN_EDIT_ADD_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

}
