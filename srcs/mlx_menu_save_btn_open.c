#include "raystruct.h"

void			menu_save_btn_open(void *gen, void *mlx)
{
	t_gen	*d;

	d = gen;
	if (d->sc)
		print_scene(d->sc);
	(void)mlx;
}
