#include "raystruct.h"

static void		perma_fade(t_mlx *m, t_img *i)
{
	static int	speed = 10;
	int			fade;

	i->i = -4;
	while ((i->i += 4) < (i->sl * m->winy))
	{
		fade = (unsigned char)i->str[i->i + 3] + (unsigned char)speed;
		if (fade > 255)
			i->str[i->i + 3] = (unsigned char)255;
		else
			i->str[i->i + 3] = (unsigned char)fade;
	}
}

void			scene_1_rt(t_mlx *m)
{
	layer(m, 2, 1);
	perma_fade(m, layer(m, 3, 0));
	mouse_over(m, m->input.mouse.over_x, m->input.mouse.over_y);
	itow(m, layer(m, 0, 0)->img, 0, 0);
	itow(m, layer(m, 1, 0)->img, 0, 0);
	itow(m, layer(m, 2, 0)->img, 0, 0);
	itow(m, layer(m, 3, 0)->img, 0, 0);
}
