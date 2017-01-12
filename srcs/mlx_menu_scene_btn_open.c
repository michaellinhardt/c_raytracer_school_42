#include "raystruct.h"

void			menu_scene_btn_open(void *ptr)
{
	t_mlx	*m;

	m = ptr;
	if (!m->menu.scene)
		ft_printf("scene btn new\n");
	else
		ft_printf("scene btn edit\n");
	(void)m;
}
