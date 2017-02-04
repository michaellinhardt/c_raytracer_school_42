/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_spot_add_btn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:41 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:42 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_spot_add_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	t_spot	*spot;

	m = mlx;
	d = gen;
	if (!m->menu.new_spot || !ft_strcmp(m->menu.new_spot
	, TXT_SPOT_ADD_NAME_DEFAUT))
		notif(m, N_WARNING, "you must enter a new spot name");
	else if (ft_strlen(m->menu.new_object) < 3)
		notif(m, N_WARNING, "spot name must have at least 3 char");
	else
	{
		if (!(spot = (t_spot *)ft_memalloc(sizeof(t_spot))))
			error(2, "ft_memalloc(t_spot)");
		ft_memcpy(spot, d->sc->spot, sizeof(t_spot));
		spot->name = m->menu.new_spot;
		m->menu.new_spot = ft_strdup(TXT_SPOT_ADD_NAME_DEFAUT);
		spot->next = d->sc->spot;
		d->sc->spot = spot;
		m->menu.spot = spot;
		menu_edit_mod_btn_open(d, m);
	}
}
