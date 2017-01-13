#include "raystruct.h"

void			menu_list_free(t_mlx *m, t_flst *flst, t_flst *destroy)
{
	if (!flst)
		return ;
	while (flst)
	{
		destroy = flst;
		flst = flst->n;
		ft_strdel(&destroy->path);
		ft_strdel(&destroy->path_preview);
		if (destroy->preview.img)
			mlx_destroy_image(m->mlx, destroy->preview.img);
		destroy->n = NULL;
		destroy->p = NULL;
		ft_memdel((void **)&destroy);
	}
	m->flst = (t_flst *)NULL;
}
