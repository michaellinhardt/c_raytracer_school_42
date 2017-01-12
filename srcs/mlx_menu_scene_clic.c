#include "raytra_gen.h"
#include "raystruct.h"

void			menu_scene_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	t_scene		*sc;
	t_scene		*last;

	last = (t_scene *)NULL;
	if (elem->scene && (sc = d->sc))
	{
		while (sc && (sc != elem->scene))
		{
			last = sc;
			sc = sc->next;
		}
		if (sc)
		{
			if (last)
			{
				last->next = sc->next;
				sc->next = d->sc;
				d->sc = sc;
			}
			if (d->sc->data)
				ft_memcpy(layer(m, 0, 0)->str, d->sc->data, W_X * W_Y * 4);
		}
	}
}
