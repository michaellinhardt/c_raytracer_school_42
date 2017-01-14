#include "raystruct.h"

static void		perma_fade(t_mlx *m, t_img *i)
{
	static int	speed = 20;
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
	static int		len = (W_X * W_Y * 4);
	if (!d->sc || (d->sc && d->sc->data))
		return ;
	if (++m->loading == 1)
		anim_init(&m->scene_img[1][ID_IMG_LOADING], FADE_IN);
	else if (m->loading == MENU_LOAD_WAIT_BEFORE_LOAD)
	{
		m->scene_img[1][ID_IMG_MENU_CADRE].fade_min = MENU_FADE_CADRE_INTERFACE;
		raytracing(d);
		ft_bzero(&m->input, sizeof(t_input));
		d->sc->data = ft_strnew(len);
		ft_memcpy(d->sc->data, d->data, len);
		ft_memcpy(layer(m, 0, 0)->str, d->sc->data, len);
		m->menu.scene = d->sc;
		m->loading = 0;
	}
	layer_add(m, layer(m, 2, 0), &m->scene_img[1][ID_IMG_LOADING]);
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
	itow(m, layer(m, 0, 0)->img, 0, 0);
	if (m->menu.draw == 1)
	{
		itow(m, layer(m, 4, 0)->img, 0, 0);
		layer(m, 2, 1);
	}
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
