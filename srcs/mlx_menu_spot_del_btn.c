/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_spot_del_btn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:51 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:51 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_spot_del_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	t_spot	*spot;
	t_spot	*last;

	m = mlx;
	d = gen;
	last = (t_spot *)NULL;
	spot = d->sc->spot;
	while (spot && (spot != m->menu.spot) && (last = spot))
		spot = spot->next;
	if (spot)
	{
		if (last)
			last->next = spot->next;
		else
			d->sc->spot = spot->next;
		spot->next = d->spot_off;
		d->spot_off = spot;
	}
	menu_reset_obj_spot(d, m);
	menu_edit_switch_btn_open(d, m);
}

void			menu_spot_del_btn_cancel(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	m->menu.next = LOAD_SPOT_EDIT;
	(void)m;
	(void)d;
}
