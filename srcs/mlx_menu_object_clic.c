#include "raytra_gen.h"
#include "raystruct.h"

void		menu_object_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	ft_printf("load object: %s\n", elem->path);
	m->menu.obj = elem->obj;
	m->menu.next = LOAD_OBJECT_EDIT;
	(void)d;
}
