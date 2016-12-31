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


#endif
