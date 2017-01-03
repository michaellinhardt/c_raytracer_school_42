#include "raystruct.h"

static void		reset_img(t_img *img, int reset)
{
	int		*ptr;
	int		color;

	if (reset == 1)
		color = 0xFF000000;
	else
		color = 0x00000000;
	img->i = -1;
	ptr = (int *)img->str;
	while (++img->i < data()->mlx.winx * data()->mlx.winy)
		ptr[img->i] = color;
}

t_img			*layer(int id, int reset)
{
	static t_img	l[LAYER_MAX];

	if (id > LAYER_MAX - 1 || id < 0)
		error(3, "macro LAYER_MAX or layer() param");
	if (!l[id].img)
	{
		ft_bzero(&l[id], sizeof(t_img));
		l[id].img = mlx_new_img(&data()->mlx, &l[id]
									, data()->mlx.winx, data()->mlx.winy);
		l[id].top[0] = 0;
		l[id].top[1] = 0;
		l[id].bot[0] = data()->mlx.winx;
		l[id].bot[1] = data()->mlx.winy;
		l[id].ptr = (int *)(l[id].str);
	}
	if (reset > 0)
		reset_img(&l[id], reset);
	return (&l[id]);
}
