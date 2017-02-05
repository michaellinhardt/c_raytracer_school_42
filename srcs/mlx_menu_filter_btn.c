/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_filter_btn.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:08 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/05 15:36:33 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_filter_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	m->menu.next = LOAD_FILTER;
	(void)gen;
}

void			menu_filter_checkbox_btn(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->menu.filter[m->menu.filter_id])
		m->menu.filter[m->menu.filter_id] = 0;
	else
		m->menu.filter[m->menu.filter_id] = 1;
	(void)gen;
}

void			menu_filter_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	int		i;

	m = mlx;
	d = gen;
	if (!d->sc || !d->sc->data)
		return ;
	if (!d->sc->data_original)
	{
		if (!(d->sc->data_original = ft_strnew(W_X * W_Y * 4)))
			error(2, "ft_strnew(d->sc->data_original)");
		ft_memcpy(d->sc->data_original, d->sc->data, W_X * W_Y * 4);
	}
	ft_memcpy(d->sc->data, d->sc->data_original, W_X * W_Y * 4);
	i = -1;
	while (++i < 14)
		if (m->menu.filter[i])
			menu_filter_call(d, i);
	ft_memcpy(layer(m, 0, 0)->str, d->sc->data, W_X * W_Y * 4);
}

void			menu_filter_btn_cancel(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	int		i;

	m = mlx;
	d = gen;
	i = -1;
	while (++i < 14)
		m->menu.filter[i] = 0;
	if (d->sc && d->sc->data_original)
	{
		if (d->sc->data)
			ft_strdel(&d->sc->data);
		if (!(d->sc->data = ft_strnew(W_X * W_Y * 4)))
			error(2, "ft_strnew(d->sc->data)");
		ft_memcpy(d->sc->data, d->sc->data_original, W_X * W_Y * 4);
	}
}

void			menu_filter(t_mlx *m, int i)
{
	if (m->menu.draw == -1 || m->menu.id != LOAD_FILTER)
		return ;
	while (++i < 14)
		if (m->menu.filter[i])
		{
			m->scene_img[1][IB_FILTER1_ON + i].status = MENU;
			m->scene_img[1][IB_FILTER1_OFF + i].status = DISABLED;
		}
		else
		{
			m->scene_img[1][IB_FILTER1_ON + i].status = DISABLED;
			m->scene_img[1][IB_FILTER1_OFF + i].status = MENU;
		}
}
