#ifndef MLX_FUNCS_H
# define MLX_FUNCS_H

void		mlx_start(t_gen *d, t_mlx *m);

char		mlx_keytochar(int key);
int			mouseo_hook(int x, int y, t_gen *d);
int			keyr_hook(int key, t_gen *d);
int			keyp_hook(int key, t_gen *d);
int			mousep_hook(int btn, int x, int y, t_gen *d);
int			mouser_hook(int btn, int x, int y, t_gen *d);

void		notif(t_mlx *m, enum e_notif type, char *msg);
void		notif2(t_mlx *m, enum e_notif type, char *str1, char *str2);
void		notif_draw(t_mlx *m, t_notif *lst, t_notif *next);
void		scene_text_notif(t_mlx *m, t_notif *lst);

void		mouse_release(t_gen *d, int btn, int x, int y);
int			mouse_release_img(t_gen *d, int btn, int x, int y);
int			mouse_release_flst(t_gen *d, t_flst *elem, int x, int y);
int			mouse_release_get(t_gen *d, int btn, int x, int y);

void		mouse_over(t_mlx *m, int x, int y);
int			area(t_img *img, t_flst *elem, int x, int y);

int			loop(t_mlx *m, char etat);
int			loopstop(t_mlx *m, char total);
int			loop_hook(t_gen *d);

void		pixel_to_char(t_gen *s, int color, int x, int y);
void		*mlx_new_img(t_mlx *m, t_img *img, int width, int heigh);
void		*mlx_xpmtostruct(t_mlx *m, t_img *img, char *file);
int			itow(t_mlx *m, void *img, int x, int y);

void		scene_img_load(t_gen *d, t_mlx *m);
void		scene_img_init(t_gen *d, t_mlx *m);
void		anim_init(t_img *img, enum e_anim anim);
void		scene_btn(t_gen *d, t_mlx *m, t_img *img, t_menu *e);
void		scene_build(t_gen *d, t_mlx *m, t_img *lay, t_img *img);
void		menu_draw_actif(t_mlx *m, t_img *img);
void		scene(t_gen *d, t_mlx *m);

void		scene_text(t_gen *d, t_mlx *m);
void		scene_text_menu(t_gen *d, t_mlx *m);
void		scene_text_input(t_mlx *m, t_get *get, int i);
void		cursor_move_left_right(t_mlx *m, t_get *g, int reset);
void		input_delete_char(t_get *g, int pos, int reset);
void		input_catch_char(t_gen *d, t_mlx *m, t_get *g, int key);
void		input_valid(t_gen *d, t_mlx *m, t_get *g);
void		input_set_focus(t_gen *d, t_mlx *m, t_get *get, int tar);
void		input_catch_char_end(t_mlx *m, t_get *g, char c);

t_img		*layer(t_mlx *m, int id, int reset);
void		layer_add(t_mlx *m, t_img *l, t_img *i);
void		layer_set_alpha(t_img *img);

void		scene_init_0_intro(t_mlx *m, t_img *img);
void		scene_init_1_rt(t_gen *d, t_mlx *m, t_img *img);
void		scene_init_1_rt_img(t_gen *d, t_mlx *m, t_img *img);
void		scene_init_1_rt_menu(t_mlx *m);

void		set_type_action(t_img *img, enum e_status status, int btn
			, void (*action)(void *gen, void *mlx));
void		set_area(t_img *img);
void		set_over_click(t_mlx *m, t_img *img, int over, int click);

void		scene_0_intro(t_mlx *m);
void		scene_0_skip(void *gen, void *mlx);

void		scene_1_rt(t_gen *d, t_mlx *m);

void		menu_list_free(t_mlx *m, t_flst *flst, t_flst *destroy);
void		menu_draw(t_mlx *m, t_flst *lst, int x, int y);

void		menu_load_btn_next(void *gen, void *mlx);
void		menu_load_btn_prev(void *gen, void *mlx);
void		menu_load_btn_open(void *gen, void *mlx);
void		menu_load_clic(t_gen *d, t_mlx *m, t_flst *elem);

void		menu_edit_mod_btn_open(void *gen, void *mlx);
void		menu_edit_switch_btn_open(void *gen, void *mlx);
void		menu_edit_add_btn_open(void *gen, void *mlx);

void		menu_edit_del_btn_open(void *gen, void *mlx);
void		menu_scene_del_btn_ok(void *gen, void *mlx);
void		menu_scene_del_btn_cancel(void *gen, void *mlx);

void		menu_scene_add_btn_ok(void *gen, void *mlx);
void		menu_scene_btn_open(void *gen, void *mlx);
void		menu_scene_clic(t_gen *d, t_mlx *m, t_flst *elem);
void		menu_reset_obj_spot(t_mlx *m);
void		menu_scene_open_order(t_gen *d, t_mlx *m);

void		menu_object_btn_open(void *gen, void *mlx);
void		menu_object_clic(t_gen *d, t_mlx *m, t_flst *elem);
void		menu_object_open_order(t_gen *d, t_mlx *m);
void		menu_object_mod_btn_type(void *gen, void *mlx);
void		menu_object_add_btn_ok(void *gen, void *mlx);
void		menu_object_del_btn_ok(void *gen, void *mlx);
void		menu_object_del_btn_cancel(void *gen, void *mlx);

void		menu_spot_btn_open(void *gen, void *mlx);
void		menu_spot_clic(t_gen *d, t_mlx *m, t_flst *elem);
void		menu_spot_open_order(t_gen *d, t_mlx *m);
void		menu_spot_mod_btn_type(void *gen, void *mlx);
void		menu_spot_add_btn_ok(void *gen, void *mlx);
void		menu_spot_del_btn_ok(void *gen, void *mlx);
void		menu_spot_del_btn_cancel(void *gen, void *mlx);

void		menu_btn_left(void *gen, void *mlx);
void		menu_btn_right(void *gen, void *mlx);
void		menu_save_btn_open(void *gen, void *mlx);
void		menu_camera_btn_open(void *gen, void *mlx);

void		scene_input(t_gen *d, t_mlx *m, int i);
char		*input_target_to_str(t_get *g);
void		scene_input_action(t_gen *d, t_mlx *m, t_get *g, t_img *lay);
void		scene_input_draw_box(t_gen *d, t_mlx *m, t_get *g, t_img *lay);
void		scene_input_draw_cursor(t_mlx *m, t_get *g, t_img *lay);

void		menu_gen_data_btn(void *gen, void *mlx);
void		menu_gen_bmp_btn(void *gen, void *mlx);

void		redraw(t_gen *d, t_mlx *m, int loading);

void		input_valid_string(t_gen *d, t_mlx *m, t_get *g);
void		input_valid_double(t_gen *d, t_mlx *m, t_get *g);
void		input_valid_double_but_int(t_gen *d, t_mlx *m, t_get *g);
void		input_valid_int(t_gen *d, t_mlx *m, t_get *g);
void		scene_text_menu_load(t_mlx *m, t_flst *elem, int i, int color);
void		scene_text_camera(t_mlx *m, int c);
void		scene_text_scene_del(t_mlx *m, int c);
void		scene_text_object_del(t_mlx *m, int c);
void		scene_text_spot_del(t_mlx *m, int c);
void		scene_text_object_mod2(t_mlx *m, int c, int i, t_img *img);
void		scene_text_spot_mod2(t_mlx *m, int c, int i, t_img *img);
void		scene_text_spot_mod(t_mlx *m, int c, char msg[512]);

void		menu_filter(t_mlx *m, int i);
void		menu_filter_btn_open(void *gen, void *mlx);
void		menu_filter_checkbox_btn(void *gen, void *mlx);
void		menu_filter_btn_ok(void *gen, void *mlx);
void		menu_filter_btn_cancel(void *gen, void *mlx);

#endif
