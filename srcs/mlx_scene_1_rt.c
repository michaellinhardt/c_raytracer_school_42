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

static void		draw_rt(t_gen *d, t_mlx *m)
{
	if (m->draw_rt < 1)
		return ;
	else if (++m->draw_rt == 2)
	{
		anim_init(&m->scene_img[1][MENU_LOAD_ID_IMG_LOADING], FADE_IN);
	}
	else if (m->draw_rt == MENU_LOAD_WAIT_BEFORE_LOAD)
	{
		raytracing(d);
		ft_bzero(&m->input, sizeof(t_input));
		m->draw_rt = 0;
		m->need_copy_data = 0;
	}
	layer_add(m, layer(m, 2, 0), &m->scene_img[1][MENU_LOAD_ID_IMG_LOADING]);
}

/*
** Layer 0: fond noir pour que les fondu fonctionne
** Layer 1: contiens le menu qui sera afficher
** Layer 2: les effet de mouse over sont dessiner la dessus
**			(et licone de loading)
** Layer 3: les effet de clic sont dessiner dessus
*/
void			scene_1_rt(t_gen *d, t_mlx *m)
{
	if (!m->need_copy_data && d->data && ++m->need_copy_data)
		ft_memcpy(layer(m, 0, 0)->str, d->data, W_X * W_Y * 4);
	itow(m, layer(m, 0, 0)->img, 0, 0);
	if (m->menu.draw == 1)
		layer(m, 2, 1);
	mouse_over(m, m->input.mouse.over_x, m->input.mouse.over_y);
	itow(m, layer(m, 1, 0)->img, 0, 0);
	itow(m, layer(m, 2, 0)->img, 0, 0);
	itow(m, layer(m, 3, 0)->img, 0, 0);
	perma_fade(m, layer(m, 1, 0));
	perma_fade(m, layer(m, 2, 0));
	perma_fade(m, layer(m, 3, 0));
	scene_text(m);
	draw_rt(d, m);
}
