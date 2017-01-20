#include "raytra_gen.h"
#include "raystruct.h"

void		menu_spot_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	ft_printf("load spot: %s\n", elem->path);
	m->menu.spot = elem->spot;
	m->menu.next = LOAD_SPOT_EDIT;
	(void)d;
}
