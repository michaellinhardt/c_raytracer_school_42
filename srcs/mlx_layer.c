#include "raystruct.h"

static void		reset_img(t_mlx *m, t_img *img, int reset)
{
	int		*ptr;
	int		color;

	if (reset == 1)
		color = 0xFF000000;
	else
		color = 0x00000000;
	img->i = -1;
	ptr = (int *)img->str;
	while (++img->i < m->winx * m->winy)
		ptr[img->i] = color;
}

t_img			*layer(t_mlx *m, int id, int reset)
{
	static t_img	l[LAYER_MAX];

	if (id > LAYER_MAX - 1 || id < 0)
		error(3, "macro LAYER_MAX or layer() param");
	if (!l[id].img)
	{
		ft_bzero(&l[id], sizeof(t_img));
		l[id].img = mlx_new_img(m, &l[id], m->winx, m->winy);
		l[id].ptr = (int *)(l[id].str);
	}
	if (reset > 0)
		reset_img(m, &l[id], reset);
	return (&l[id]);
}
