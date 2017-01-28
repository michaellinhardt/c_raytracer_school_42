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

static void			scene_img_copy(t_mlx *m, t_img *src, t_img *dst)
{
	dst->width = src->width;
	dst->heigh = src->heigh;
	dst->fade_min = src->fade_min;
	dst->fade_max = src->fade_max;
	dst->set_alpha = src->set_alpha;
	dst->menu = src->menu;
	dst->pos[0] = src->pos[0];
	dst->pos[1] = src->pos[1];
	set_type_action(dst, src->status, src->mouse.btn, src->mouse.action);
	if (!dst->img)
		dst->img = mlx_new_img(m, dst, src->width, src->heigh);
	dst->i = -1;
	while (++dst->i < dst->width * dst->heigh)
		dst->ptr[dst->i] = src->ptr[dst->i];
	set_area(dst);
}

static void			scene_init_1_rt_input(t_gen *d, t_mlx *m, t_get *g)
{
	g = &m->get[ID_INPUT_ADD_SCENE_NAME];
	g->menu = LOAD_SCENE_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_scene = ft_strdup(TXT_SCENE_ADD_NAME_DEFAUT);
	g->name = ft_strdup(TXT_SCENE_ADD_NAME);
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
	g->name = ft_strdup(TXT_SCENE_MOD_NAME);
	g->size_min = 3;
	g->size_max = 59;

	g = &m->get[ID_INPUT_SCENE_AMBIANCE1];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_HEXA_TO_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_MOD_SCENE_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_MOD_SCENE_NAME].box.pos[1]
	+ INPUT_SIZE_CHAR_Y * 2 + 15;
	g->name = ft_strdup(TXT_SCENE_MOD_AMB1);
	g->size_min = 6;
	g->size_max = 7;

	g = &m->get[ID_INPUT_SCENE_AMBIANCE2];
	g->menu = LOAD_SCENE_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[0] + 347;
	g->box.pos[1] = m->get[ID_INPUT_SCENE_AMBIANCE1].box.pos[1];
	g->name = ft_strdup(TXT_SCENE_MOD_AMB2);
	g->size_min = 3;
	g->size_max = 25;

	g = &m->get[ID_INPUT_OBJECT_NAME];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_STRING_FILE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[0] + 15;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[1] + 40;
	g->name = ft_strdup(TXT_OBJECT_MOD_NAME);
	g->size_min = 3;
	g->size_max = 59;

	g = &m->get[ID_INPUT_OBJECT_COLOR];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_HEXA;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_NAME].box.pos[0] + 710;
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_NAME].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_COLOR);
	g->size_min = 6;
	g->size_max = 7;

	g = &m->get[ID_INPUT_OBJECT_POS1];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_NAME].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_NAME].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_POS1);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_POS2];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS2);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_POS3];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS2].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS3);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_POS4];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS1].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_POS1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_POS4);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_POS5];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS5);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_POS6];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_POS6);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_SIZE1];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_POS4].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_SIZE1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_SIZE1);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_SIZE2];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_SIZE1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_SIZE2);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_SIZE3];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_SIZE1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_SIZE3);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_EFF1];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_SIZE3].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_NAME].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF1);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_EFF2];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF2);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_EFF3];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF1].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF3);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_EFF4];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF1].box.pos[1] + 10
	+ m->get[ID_INPUT_OBJECT_POS1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF4);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_EFF5];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF5);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_OBJECT_EFF6];
	g->menu = LOAD_OBJECT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_OBJECT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_OBJECT_EFF4].box.pos[1];
	g->name = ft_strdup(TXT_OBJECT_MOD_EFF6);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_ADD_OBJECT_NAME];
	g->menu = LOAD_OBJECT_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_object = ft_strdup(TXT_OBJECT_ADD_NAME_DEFAUT);
	g->name = ft_strdup(TXT_OBJECT_ADD_NAME);
	g->target.ptr_str = &m->menu.new_object;
	g->box.pos[0] = 541;
	g->box.pos[1] = 483;
	g->size_min = 3;
	g->size_max = 59;

	g = &m->get[ID_INPUT_SPOT_NAME];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_STRING_FILE;
	g->box.pos[0] = m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[0] + 15;
	g->box.pos[1] = m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[1] + 40;
	g->name = ft_strdup(TXT_SPOT_MOD_NAME);
	g->size_min = 3;
	g->size_max = 59;

	g = &m->get[ID_INPUT_SPOT_COLOR];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_HEXA;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_NAME].box.pos[0] + 710;
	g->box.pos[1] = m->get[ID_INPUT_SPOT_NAME].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_COLOR);
	g->size_min = 6;
	g->size_max = 7;

	g = &m->get[ID_INPUT_SPOT_POS1];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_NAME].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_NAME].box.pos[1] + 10
	+ m->get[ID_INPUT_SPOT_NAME].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_SPOT_MOD_POS1);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_SPOT_POS2];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS1].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS1].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS2);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_SPOT_POS3];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS2].box.pos[0] + 330;
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS2].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS3);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_SPOT_POS4];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS1].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS1].box.pos[1] + 10
	+ m->get[ID_INPUT_SPOT_POS1].box.heigh * 2 + INPUT_SIZE_CHAR_Y * 2;
	g->name = ft_strdup(TXT_SPOT_MOD_POS4);
	g->size_min = 3;
	g->size_max = 17;

	g = &m->get[ID_INPUT_SPOT_POS5];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS2].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS5);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_SPOT_POS6];
	g->menu = LOAD_SPOT_EDIT;
	g->mode = MODE_DOUBLE;
	g->box.pos[0] = m->get[ID_INPUT_SPOT_POS3].box.pos[0];
	g->box.pos[1] = m->get[ID_INPUT_SPOT_POS4].box.pos[1];
	g->name = ft_strdup(TXT_SPOT_MOD_POS6);
	g->size_min = 1;
	g->size_max = 17;

	g = &m->get[ID_INPUT_ADD_SPOT_NAME];
	g->menu = LOAD_SPOT_ADD;
	g->mode = MODE_STRING_FILE;
	m->menu.new_spot = ft_strdup(TXT_SPOT_ADD_NAME_DEFAUT);
	g->name = ft_strdup(TXT_SPOT_ADD_NAME);
	g->target.ptr_str = &m->menu.new_spot;
	g->box.pos[0] = 541;
	g->box.pos[1] = 483;
	g->size_min = 3;
	g->size_max = 59;

	(void)d;
}

void			scene_init_1_rt_img(t_gen *d, t_mlx *m, t_img *img)
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

	img = &m->scene_img[1][IMENU_EDIT_OBJECT_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_OBJECT_EDIT;
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

	img = &m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SCENE_DEL;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	img = &m->scene_img[1][IB_SCENE_DEL_OK];
	img->pos[0] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].width - img->width * 2 - 5;
	img->pos[1] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].heigh - img->heigh - 17;
	img->menu = LOAD_SCENE_DEL;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_del_btn_ok);
	set_over_click(m, img
		, IB_SCENE_DEL_OK_OVER, IB_SCENE_DEL_OK_CLICK);

	img = &m->scene_img[1][IB_SCENE_DEL_CANCEL];
	img->pos[0] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].width - img->width * 1 - 5;
	img->pos[1] = m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1]
	+ m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].heigh - img->heigh - 20;
	img->menu = LOAD_SCENE_DEL;
	img->fade_min = 40;
	img->set_alpha = -1;
	set_area(img);
	set_type_action(img, MENU, 1, &menu_scene_del_btn_cancel);
	set_over_click(m, img
		, IB_SCENE_DEL_CANCEL_OVER, IB_SCENE_DEL_CANCEL_CLICK);

	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	img->pos[0] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[0] + 360;
	img->pos[1] = m->scene_img[1][IMENU_EDIT_OBJECT_BOX].pos[1]
	+ m->scene_img[1][IMENU_EDIT_OBJECT_BOX].heigh - 80 - img->heigh * 2;

	set_type_action(img, DISABLED, 8, NULL);

	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 8, NULL);

	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 8, NULL);

	img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT];
	img->menu = LOAD_OBJECT_EDIT;
	img->fade_min = 80;
	img->set_alpha = -1;
	set_type_action(img, DISABLED, 8, NULL);

	int		i;
	i = 0;
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF], img);
		img->pos[0] += (i % 3 - 1) * 320;
		if (i > 3 && i < 7)
			img->pos[1] += (img->heigh + 10);
		else if (i > 6)
			img->pos[1] += (img->heigh + 10) * 2;
		set_area(img);
		set_type_action(img, MENU, 8, NULL);
	}

	i = 0;
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF9 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER], img);
		img->pos[0] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF9 + i - 9].pos[0];
		img->pos[1] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF9 + i - 9].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}

	i = 0;
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER9 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT], img);
		img->pos[0] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER9 + i - 9].pos[0];
		img->pos[1] = m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER9 + i - 9].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}

	i = 0;
	while (++i < 10)
	{
		img = &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT9 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE], img);
		img->pos[0] = m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT9 + i - 9].pos[0];
		img->pos[1] = m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT9 + i - 9].pos[1];
		set_area(img);
		set_type_action(img, MENU, 1, &menu_object_mod_btn_type);
		set_over_click(m, img
		, (IB_OBJECT_MOD_TYPE_SELECT9 + i) - 18
		, (IB_OBJECT_MOD_TYPE_SELECT9 + i) - 9);
	}

	img = &m->scene_img[1][IMENU_ADD_OBJECT_BOX];
	scene_img_copy(m, &m->scene_img[1][IMENU_ADD_SCENE_BOX], img);
	img->menu = LOAD_OBJECT_ADD;
	img = &m->scene_img[1][IB_OBJECT_ADD_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK], img);
	img->menu = LOAD_OBJECT_ADD;
	img = &m->scene_img[1][IB_OBJECT_ADD_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_OVER], img);
	img->menu = LOAD_OBJECT_ADD;
	img = &m->scene_img[1][IB_OBJECT_ADD_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_CLICK], img);
	img->menu = LOAD_OBJECT_ADD;

	img = &m->scene_img[1][IB_OBJECT_ADD_OK];
	set_type_action(img, MENU, 1, &menu_object_add_btn_ok);
	set_over_click(m, img
		, IB_OBJECT_ADD_OK_OVER, IB_OBJECT_ADD_OK_CLICK);

	img = &m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL];
	scene_img_copy(m, &m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_OVER], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_CLICK], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK], img);
	img->menu = LOAD_OBJECT_DEL;
	set_type_action(img, MENU, 1, &menu_object_del_btn_ok);
	set_over_click(m, img
		, IB_OBJECT_DEL_OK_OVER, IB_OBJECT_DEL_OK_CLICK);
	img = &m->scene_img[1][IB_OBJECT_DEL_CANCEL_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_OVER], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_CANCEL_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_CLICK], img);
	img->menu = LOAD_OBJECT_DEL;
	img = &m->scene_img[1][IB_OBJECT_DEL_CANCEL];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL], img);
	img->menu = LOAD_OBJECT_DEL;
	set_type_action(img, MENU, 1, &menu_object_del_btn_cancel);
	set_over_click(m, img
		, IB_OBJECT_DEL_CANCEL_OVER, IB_OBJECT_DEL_CANCEL_CLICK);

	img = &m->scene_img[1][IMENU_EDIT_SPOT_BOX_DEL];
	scene_img_copy(m, &m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_OVER], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK_CLICK], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_OK], img);
	img->menu = LOAD_SPOT_DEL;
	set_type_action(img, MENU, 1, &menu_spot_del_btn_ok);
	set_over_click(m, img
	, IB_SPOT_DEL_OK_OVER, IB_SPOT_DEL_OK_CLICK);
	img = &m->scene_img[1][IB_SPOT_DEL_CANCEL_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_OVER], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_CANCEL_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL_CLICK], img);
	img->menu = LOAD_SPOT_DEL;
	img = &m->scene_img[1][IB_SPOT_DEL_CANCEL];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_DEL_CANCEL], img);
	img->menu = LOAD_SPOT_DEL;
	set_type_action(img, MENU, 1, &menu_spot_del_btn_cancel);
	set_over_click(m, img
	, IB_SPOT_DEL_CANCEL_OVER, IB_SPOT_DEL_CANCEL_CLICK);

	img = &m->scene_img[1][IMENU_EDIT_SPOT_BOX];
	img->pos[0] = (m->winx / 2) - (img->width / 2);
	img->pos[1] = (m->winy / 2) - (img->heigh / 2);
	img->menu = LOAD_SPOT_EDIT;
	img->fade_min = MENU_FADE_ADD_SCENE;
	img->set_alpha = -1;
	set_type_action(img, MENU, 0, NULL);

	i = 0;
	while (++i < 3)
	{
		img = &m->scene_img[1][IMENU_EDIT_SPOT_BOX + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OFF], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = 50 + m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[0]
		+ (i * 200);
		img->pos[1] = m->scene_img[1][IMENU_EDIT_SPOT_BOX].pos[1]
		+ m->scene_img[1][IMENU_EDIT_SPOT_BOX].heigh - 100;
		set_area(img);
		set_type_action(img, MENU, 8, NULL);
	}

	i = 0;
	while (++i < 3)
	{
		img = &m->scene_img[1][IB_SPOT_MOD_TYPE_OFF2 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_OVER], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = m->scene_img[1][IB_SPOT_MOD_TYPE_OFF2 + i - 2].pos[0];
		img->pos[1] = m->scene_img[1][IB_SPOT_MOD_TYPE_OFF2 + i - 2].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}

	i = 0;
	while (++i < 3)
	{
		img = &m->scene_img[1][IB_SPOT_MOD_TYPE_OVER2 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE_SELECT], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = m->scene_img[1][IB_SPOT_MOD_TYPE_OVER2 + i - 2].pos[0];
		img->pos[1] = m->scene_img[1][IB_SPOT_MOD_TYPE_OVER2 + i - 2].pos[1];
		set_area(img);
		set_type_action(img, DISABLED, 8, NULL);
	}

	i = 0;
	while (++i < 3)
	{
		img = &m->scene_img[1][IB_SPOT_MOD_TYPE_SELECT2 + i];
		scene_img_copy(m, &m->scene_img[1][IB_OBJECT_MOD_TYPE], img);
		img->menu = LOAD_SPOT_EDIT;
		img->pos[0] = m->scene_img[1][IB_SPOT_MOD_TYPE_SELECT2 + i - 2].pos[0];
		img->pos[1] = m->scene_img[1][IB_SPOT_MOD_TYPE_SELECT2 + i - 2].pos[1];
		set_area(img);
		set_type_action(img, MENU, 1, &menu_spot_mod_btn_type);
		set_over_click(m, img
		, (IB_SPOT_MOD_TYPE_SELECT2 + i) - 4
		, (IB_SPOT_MOD_TYPE_SELECT2 + i) - 2);
	}

	img = &m->scene_img[1][IMENU_ADD_SPOT_BOX];
	scene_img_copy(m, &m->scene_img[1][IMENU_ADD_SCENE_BOX], img);
	img->menu = LOAD_SPOT_ADD;
	img = &m->scene_img[1][IB_SPOT_ADD_OK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK], img);
	img->menu = LOAD_SPOT_ADD;
	img = &m->scene_img[1][IB_SPOT_ADD_OK_OVER];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_OVER], img);
	img->menu = LOAD_SPOT_ADD;
	img = &m->scene_img[1][IB_SPOT_ADD_OK_CLICK];
	scene_img_copy(m, &m->scene_img[1][IB_SCENE_ADD_OK_CLICK], img);
	img->menu = LOAD_SPOT_ADD;

	img = &m->scene_img[1][IB_SPOT_ADD_OK];
	set_type_action(img, MENU, 1, &menu_spot_add_btn_ok);
	set_over_click(m, img
		, IB_SPOT_ADD_OK_OVER, IB_SPOT_ADD_OK_CLICK);

	scene_init_1_rt_input(d, m, (t_get *)NULL);
	scene_init_1_rt_input_area(m, (t_get *)NULL, -1);
}
