#ifndef MLX_FUNCS_H
# define MLX_FUNCS_H

void		mlx_start(t_gen *d, t_mlx *m);

int			mouseo_hook(int x, int y, t_gen *d);
int			keyr_hook(int key, t_gen *d);
int			keyp_hook(int key, t_gen *d);
int			mousep_hook(int btn, int x, int y, t_gen *d);
int			mouser_hook(int btn, int x, int y, t_gen *d);

void		mouse_release(t_gen *d, int btn, int x, int y);
void		mouse_over(t_mlx *m, int x, int y);
int			area(t_img *img, t_flst *elem, int x, int y);

int			loop(t_mlx *m, char etat);
int			loopstop(t_mlx *m, char total);
int			loop_hook(t_gen *d);

void		pixel_to_char(t_gen *s, int color, int x, int y);
void		*mlx_new_img(t_mlx *m, t_img *img, int width, int heigh);
void		*mlx_xpmtostruct(t_mlx *m, t_img *img, char *file);
int			itow(t_mlx *m, void *img, int x, int y);

void		scene_img_load(t_mlx *m);
void		scene_img_init(t_mlx *m);
void		anim_init(t_img *img, enum e_anim anim);
void		scene_build(t_mlx *m, t_img *lay, t_img *img, int i);
void		scene_text(t_mlx *m);
void		scene(t_gen *d, t_mlx *m);

t_img		*layer(t_mlx *m, int id, int reset);
void		layer_add(t_mlx *m, t_img *l, t_img *i);

void		scene_init_0_intro(t_mlx *m, t_img *img);
void		scene_init_1_rt(t_mlx *m, t_img *img);
void		scene_init_1_rt_menu(t_mlx *m);

void		scene_0_intro(t_mlx *m);
void		scene_0_skip(void *ptr);

void		scene_1_rt(t_gen *d, t_mlx *m);

void		menu_load_btn_next(void *ptr);
void		menu_load_btn_prev(void *ptr);
void		menu_load_btn_open(void *ptr);
void		menu_load_draw(t_mlx *m, t_flst *lst, int x, int y);

#endif
