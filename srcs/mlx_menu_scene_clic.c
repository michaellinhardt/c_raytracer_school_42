/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_scene_clic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:37 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/12 14:18:43 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

int				menu_reset_cam(t_gen *d)
{
	if (d->mlx.menu.draw == 1)
		return (0);
	d->view_angle.x = 0;
	d->view_angle.y = 0;
	d->view_angle.z = 0;
	if (d->sc)
		redraw(d, &d->mlx, 1);
	return (0);
}

void			menu_reset_obj_spot(t_gen *d, t_mlx *m)
{
	m->menu.obj = NULL;
	m->menu.spot = NULL;
	if (d->sc)
	{
		if (d->sc->obj)
			m->menu.obj = d->sc->obj;
		if (d->sc->spot)
			m->menu.spot = d->sc->spot;
	}
	d->view_angle.x = 0;
	d->view_angle.y = 0;
	d->view_angle.z = 0;
}

void			menu_scene_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	t_scene		*sc;
	t_scene		*last;

	last = (t_scene *)NULL;
	sc = (t_scene *)NULL;
	if (elem->scene && (sc = d->sc))
	{
		while (sc && (sc != elem->scene) && (last = sc))
			sc = sc->next;
		if (sc)
		{
			if (last)
			{
				last->next = sc->next;
				sc->next = d->sc;
				d->sc = sc;
			}
			if (d->sc->data)
				ft_memcpy(layer(m, 0, 0)->str, d->sc->data, W_X * W_Y * 4);
		}
	}
	menu_reset_obj_spot(d, m);
	m->menu.scene = d->sc;
	menu_edit_mod_btn_open((void *)d, (void *)m);
}
