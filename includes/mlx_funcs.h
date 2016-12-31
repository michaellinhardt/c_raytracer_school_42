#ifndef MLX_FUNCS_H
# define MLX_FUNCS_H

void		mlx_start(t_gen *d, t_mlx *m);

int			mouseo_hook(int x, int y, t_gen *d);
int			keyr_hook(int key, t_gen *d);
int			keyp_hook(int key, t_gen *d);
int			mousep_hook(int btn, int x, int y, t_gen *d);
int			mouser_hook(int btn, int x, int y, t_gen *d);

int			loop(t_mlx *m, char etat);
int			loopstop(t_mlx *m, char total);
int			loop_hook(t_gen *d);

void		pixel_to_char(t_gen *s, int color, int x, int y);
void		*mlx_new_img(t_mlx *m, t_img *img, int width, int heigh);
void		*mlx_xpmtostruct(t_mlx *m, t_img *img, char *file);
int			itow(t_mlx *m, void *img, int x, int y);

#endif
