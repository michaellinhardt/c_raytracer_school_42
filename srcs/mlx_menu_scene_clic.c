#include "raytra_gen.h"
#include "raystruct.h"

void		menu_scene_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	ft_printf("load scene: %s\n", elem->path);
	(void)d;
	(void)m;
	(void)elem;
}
