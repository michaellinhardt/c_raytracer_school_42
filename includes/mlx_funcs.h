#ifndef MLX_FUNCS_H
# define MLX_FUNCS_H

void		mlx_start(t_gen *d, t_mlx *m);

int			mouseo_hook(int x, int y, t_gen *d);
int			keyr_hook(int key, t_gen *d);
int			keyp_hook(int key, t_gen *d);
int			mousep_hook(int btn, int x, int y, t_gen *d);
int			mouser_hook(int btn, int x, int y, t_gen *d);

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
void		scene_btn(t_gen *d, t_mlx *m, t_img *img);
void		scene_build(t_gen *d, t_mlx *m, t_img *lay, t_img *img);
void		menu_draw_actif(t_mlx *m, t_img *img);
void		scene(t_gen *d, t_mlx *m);

void		scene_text(t_gen *d, t_mlx *m);
void		scene_text_menu(t_gen *d, t_mlx *m);
void		scene_text_input(t_mlx *m, t_get *get, int i);
int			cursor_move_left_right(t_mlx *m, t_get *g, int ret);

t_img		*layer(t_mlx *m, int id, int reset);
void		layer_add(t_mlx *m, t_img *l, t_img *i);
void		layer_set_alpha(t_img *img);

void		scene_init_0_intro(t_mlx *m, t_img *img);
void		scene_init_1_rt(t_gen *d, t_mlx *m, t_img *img);
void		scene_init_1_rt_img(t_mlx *m, t_img *img);
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

void		menu_edit_add_btn_open(void *gen, void *mlx);

void		menu_scene_add_btn_ok(void *gen, void *mlx);
void		menu_scene_add_btn_cancel(void *gen, void *mlx);
void		menu_scene_btn_open(void *gen, void *mlx);
void		menu_scene_clic(t_gen *d, t_mlx *m, t_flst *elem);

void		menu_object_btn_open(void *gen, void *mlx);
void		menu_object_clic(t_gen *d, t_mlx *m, t_flst *elem);

void		menu_spot_btn_open(void *gen, void *mlx);
void		menu_spot_clic(t_gen *d, t_mlx *m, t_flst *elem);

void		menu_btn_left(void *gen, void *mlx);
void		menu_btn_right(void *gen, void *mlx);
void		menu_save_btn_open(void *gen, void *mlx);
void		menu_camera_btn_open(void *gen, void *mlx);

void		scene_input(t_gen *d, t_mlx *m, int i);
char		*input_target_to_str(t_get *g);
void		scene_input_action(t_gen *d, t_mlx *m, t_get *g, t_img *lay);
void		scene_input_buff(t_gen *d, t_mlx *m, t_get *g, t_img *lay);
void		scene_input_draw_box(t_gen *d, t_mlx *m, t_get *g, t_img *lay);
void		scene_input_draw_cursor(t_mlx *m, t_get *g, t_img *lay);

#endif
