#include "raytra_gen.h"
#include "raystruct.h"

void		menu_spot_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	m->menu.spot = elem->spot;
	m->menu.next = LOAD_SPOT_EDIT;
	menu_edit_mod_btn_open(d, m);
}
