#include "raytra_gen.h"
#include "raystruct.h"

void		menu_object_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	ft_printf("load object: %s\n", elem->path);
	m->menu.obj = elem->obj;
	m->menu.id = LOAD_OBJECT;
	menu_edit_mod_btn_open(d, m);
	(void)d;
}
