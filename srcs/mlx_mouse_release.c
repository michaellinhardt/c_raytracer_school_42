#include "raytra_gen.h"
#include "raystruct.h"

void			mouse_release(t_gen *d, int btn, int x, int y)
{
	if (mouse_release_get(d, btn, x, y))
		return ;
	else if (btn == 1 && mouse_release_flst(d, d->mlx.flst, x, y))
		return ;
	else if (mouse_release_img(d, btn, x, y))
		return ;
}
