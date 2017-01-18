#include "raystruct.h"

void			menu_edit_del_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	m->menu.next = LOAD_SCENE_DEL;
}
