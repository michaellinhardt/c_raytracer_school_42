#include "raystruct.h"

void			scene_0_skip(void *ptr)
{
	t_mlx	*m;

	m = ptr;
	// if (m->scene_img[0][0].anim.id == )
	m->scene_img[0][0].anim.id = FADE_OUT;
	ft_printf("zbra, win size: %d\n", m->winx);
}
