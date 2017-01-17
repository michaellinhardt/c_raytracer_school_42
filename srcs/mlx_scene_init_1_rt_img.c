# include "raytra_gen.h"
# include "raystruct.h"

static void			scene_init_1_rt_input_area(t_mlx *m, t_get *g, int i)
{
	while (++i < GET_APP_MAX)
	{
		if (!(g = &m->get[i])->menu)
			continue ;
		g->box.mouse.top[0] = g->box.pos[0];
		g->box.mouse.top[1] = g->box.pos[1];
		g->box.width = INPUT_SIZE_CHAR_X * g->size_max + INPUT_PADDING;
		g->box.heigh = INPUT_SIZE_CHAR_Y + INPUT_PADDING;
		g->box.mouse.bot[0] = g->box.pos[0] + g->box.width;
		g->box.mouse.bot[1] = g->box.pos[1] + g->box.heigh;
	}
}

static void			scene_init_1_rt_input(t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_ADD_SCENE_NAME];
	g->menu = LOAD_SCENE_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_scene = ft_strdup(TXT_SCENE_ADD_NAME_DEFAUT);
	g->target.ptr_str = &m->menu.new_scene;
	g->box.pos[0] = 541;
	g->box.pos[1] = 483;
	g->size_min = 3;
	g->size_max = 59;

	g = &m->get[ID_INPUT_MOD_SCENE_NAME];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_STRING_FILE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_SCENE_BOX].pos[0] + 15;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_SCENE_BOX].pos[1] + 40;
	g->size_min = 3;
	g->size_max = 59;

	g = &m->get[ID_INPUT_SCENE_AMBIANCE1];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_MOD_SCENE_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_MOD_SCENE_NAME].box.pos[1]
	+ INPUT_SIZE_CHAR_Y * 2 + 15;
	g->size_min = 3;
	g->size_max = 25;

	g = &m->get[ID_INPUT_SCENE_AMBIANCE2];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[0] + 347;
	g->box.pos[1] = m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[1];
	g->size_min = 3;
	g->size_max = 25;
}

void			scene_init_1_rt_img(t_mlx *m, t_img *img)
{

	img = &m->getcursor;
	img->width = 2;
	img->heigh = INPUT_SIZE_CHAR_Y - INPUT_PADDING;
	img->img = mlx_new_img(m, img, img->width, img->heigh);
	img->i = -1;
	while (++img->i < img->width * img->heigh)
		img->ptr[img->i] = INPUT_CURSOR_COLOR;
	img->fade_min = 1;
	img->fade_max = 255;

	img = &m->scene_img[1][IMENU_CADRE];
	img->fade_min = 110;
	img->set_alpha = 0xFF000000;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IMENU_CADRE_LIGHTNING];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = 4;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IMENU_CADRE_LOGO];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = 22;
	img->fade_min = 100;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_LOAD];
	img->pos[0] = 530;
	img->pos[1] = 11;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_load_btn_open);
	set_over_click(m, img, IB_LOAD_OVER, IB_LOAD_CLICK);

	img = &m->scene_img[1][IB_SAVE];
	img->pos[0] = 1095;
	img->pos[1] = m->scene_img[1][IB_LOAD].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_save_btn_open);
	set_over_click(m, img, IB_SAVE_OVER, IB_SAVE_CLICK);

	img = &m->scene_img[1][IB_SCENE];
	img->pos[0] = 677;
	img->pos[1] = 960;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_btn_open);
	set_over_click(m, img, IB_SCENE_OVER, IB_SCENE_CLICK);

	img = &m->scene_img[1][IB_OBJECT];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0]
	+ (img->width * 1) + (BOT_BTN_X_DECALLAGE * 1);
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_object_btn_open);
	set_over_click(m, img, IB_OBJECT_OVER, IB_OBJECT_CLICK);

	img = &m->scene_img[1][IB_SPOT];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0]
	+ (img->width * 2) + (BOT_BTN_X_DECALLAGE * 2);
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_spot_btn_open);
	set_over_click(m, img, IB_SPOT_OVER, IB_SPOT_CLICK);

	img = &m->scene_img[1][IB_CAMERA];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0]
	+ (img->width * 3) + (BOT_BTN_X_DECALLAGE * 3);
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_camera_btn_open);
	set_over_click(m, img, IB_CAMERA_OVER, IB_CAMERA_CLICK);

	img = &m->scene_img[1][IB_ARROW_LEFT_OFF];
	img->pos[0] = 8;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_ARROW_LEFT];
	img->menu = LOAD_FILE;
	img->pos[0] = m->scene_img[1][IB_ARROW_LEFT_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_ARROW_LEFT_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_btn_left);
	set_over_click(m, img
		, IB_ARROW_LEFT_OVER, IB_ARROW_LEFT_CLICK);

	img = &m->scene_img[1][IB_ARROW_RIGHT_OFF];
	img->pos[0] = m->winx - img->width - 8;
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_ARROW_RIGHT];
	img->menu = LOAD_FILE;
	img->pos[0] = m->scene_img[1][IB_ARROW_RIGHT_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_ARROW_RIGHT_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, DISABLED, 1, &menu_btn_right);
	set_over_click(m, img
		, IB_ARROW_RIGHT_OVER, IB_ARROW_RIGHT_CLICK);

	img = &m->scene_img[1][IMG_PREVIEW_NO_IMG];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);

	img = &m->scene_img[1][IMG_PREVIEW];
	img->fade_min = 100;
	img->set_alpha = -1;
	layer_set_alpha(img);

	img = &m->scene_img[1][IMG_PREVIEW_OVER];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);

	img = &m->scene_img[1][IMG_PREVIEW_CLIC];
	img->fade_min = 50;
	img->set_alpha = -1;
	layer_set_alpha(img);


	// BOUTON OFF
	img = &m->scene_img[1][IB_SCENE_OFF];
	img->pos[0] = m->scene_img[1][IB_SCENE].pos[0];
	img->pos[1] = m->scene_img[1][IB_SCENE].pos[1];
	img->fade_min = m->scene_img[1][IB_SCENE].fade_min;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 0, NULL);


	img = &m->scene_img[1][IB_OBJECT_OFF];
	img->pos[0] = m->scene_img[1][IB_OBJECT].pos[0];
	img->pos[1] = m->scene_img[1][IB_OBJECT].pos[1];
	img->fade_min = m->scene_img[1][IB_OBJECT].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_SPOT_OFF];
	img->pos[0] = m->scene_img[1][IB_SPOT].pos[0];
	img->pos[1] = m->scene_img[1][IB_SPOT].pos[1];
	img->fade_min = m->scene_img[1][IB_SPOT].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_CAMERA_OFF];
	img->pos[0] = m->scene_img[1][IB_CAMERA].pos[0];
	img->pos[1] = m->scene_img[1][IB_CAMERA].pos[1];
	img->fade_min = m->scene_img[1][IB_CAMERA].fade_min;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);


	img = &m->scene_img[1][IB_E_MOD_OFF];
	img->pos[0] = 153;
	img->pos[1] = 952;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_E_MOD];
	img->pos[0] = m->scene_img[1][IB_E_MOD_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_MOD_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_mod_btn_open);
	set_over_click(m, img, IB_E_MOD_OVER, IB_E_MOD_CLICK);



	img = &m->scene_img[1][IB_E_ADD_OFF];
	img->pos[0] = m->scene_img[1][IB_E_MOD_OFF].pos[0]
	+ (img->width * 1) + (BOT_BTN_X_DECALLAGE * 1);
	img->pos[1] = m->scene_img[1][IB_E_MOD_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_E_ADD];
	img->pos[0] = m->scene_img[1][IB_E_ADD_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_ADD_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_add_btn_open);
	set_over_click(m, img, IB_E_ADD_OVER, IB_E_ADD_CLICK);



	img = &m->scene_img[1][IB_E_SWITCH_OFF];
	img->pos[0] = m->scene_img[1][IB_E_MOD_OFF].pos[0]
	+ (img->width * 2) + (BOT_BTN_X_DECALLAGE * 2);
	img->pos[1] = m->scene_img[1][IB_E_MOD_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_E_SWITCH];
	img->pos[0] = m->scene_img[1][IB_E_SWITCH_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_SWITCH_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_switch_btn_open);
	set_over_click(m, img, IB_E_SWITCH_OVER, IB_E_SWITCH_CLICK);

	img = &m->scene_img[1][IB_E_DEL_OFF];
	img->pos[0] = m->scene_img[1][IB_E_MOD_OFF].pos[0]
	+ (img->width * 3) + (BOT_BTN_X_DECALLAGE * 3);
	img->pos[1] = m->scene_img[1][IB_E_MOD_OFF].pos[1];
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_E_DEL];
	img->pos[0] = m->scene_img[1][IB_E_DEL_OFF].pos[0];
	img->pos[1] = m->scene_img[1][IB_E_DEL_OFF].pos[1];
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_edit_del_btn_open);
	set_over_click(m, img, IB_E_DEL_OVER, IB_E_DEL_CLICK);

	img = &m->scene_img[1][IB_SELECTED];
	img->fade_min = 100;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 0, NULL);

	img = &m->scene_img[1][IMENU_ADD_SCENE_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SCENE_ADD;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IMENU_EDIT_SCENE_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SCENE_EDIT;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_SCENE_ADD_OK];
	img->pos[0] = m->scene_img[1][IMENU_ADD_SCENE_BOX].pos[0]
	+ m->scene_img[1][IMENU_ADD_SCENE_BOX].width - img->width - 5;
	img->pos[1] = m->scene_img[1][IMENU_ADD_SCENE_BOX].pos[1]
	+ m->scene_img[1][IMENU_ADD_SCENE_BOX].heigh - img->heigh - 5;
	img->menu = LOAD_SCENE_ADD;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_add_btn_ok);
	set_over_click(m, img
		, IB_SCENE_ADD_OK_OVER, IB_SCENE_ADD_OK_CLICK);



	scene_init_1_rt_input(m, (t_get *)NULL);
	scene_init_1_rt_input_area(m, (t_get *)NULL, -1);
}
