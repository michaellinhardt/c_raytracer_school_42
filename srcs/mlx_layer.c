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
		img->ptr[img->i] = color;
}

static void		anim_eval(t_img *img)
{
	if (img->anim.id == FADE_IN && img->fade > 0)
	{
		img->fade -= img->anim.tempo;
		if (img->fade <= 0)
		{
			img->fade = 0;
			img->anim.id = STATIC;
		}
	}
	if (img->anim.id == FADE_OUT && img->fade < 255)
	{
		img->fade += img->anim.tempo;
		if (img->fade >= 255)
		{
			img->fade = 255;
			img->anim.id = STATIC;
		}
	}
}

static void		set_alpha(t_img *img, int color)
{
	img->i = -1;
	while (++img->i < img->width * img->heigh)
	{
		if (img->i == 0)
			color = img->ptr[img->i];
		if (img->ptr[img->i] == color)
			img->ptr[img->i] = 0xFF666999;
	}
	img->set_alpha = 0;
}

void			layer_add(t_mlx *m, t_img *l, t_img *i)
{
	int		*layer;
	int		*img;
	int		x;
	int		y;
	int		pos;

	layer = (int *)l->str;
	img = (int *)i->str;
	l->i = (m->winx * i->pos[1] + i->pos[0]) - 1;
	y = -1;
	anim_eval(i);
	if (i->set_alpha == 1)
		set_alpha(i, -1);
	while (++y < i->heigh)
	{
		x = -1;
		while (++x < i->width)
		{
			if (i->ptr[(pos = y * i->width + x)] != (int)0xFF666999)
				i->str[pos * 4 + 3] = i->fade;
			layer[++(l->i)] = img[y * i->width + x];
		}
		l->i = l->i - i->width + m->winx;
	}
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
