/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_object_del_btn.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:26 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:27 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_object_del_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;
	t_obj	*obj;
	t_obj	*last;

	m = mlx;
	d = gen;
	last = (t_obj *)NULL;
	obj = d->sc->obj;
	while (obj && (obj != m->menu.obj) && (last = obj))
		obj = obj->next;
	if (obj)
	{
		if (last)
			last->next = obj->next;
		else
			d->sc->obj = obj->next;
		obj->next = d->obj_off;
		d->obj_off = obj;
	}
	menu_reset_obj_spot(d, m);
	menu_edit_switch_btn_open(d, m);
}

void			menu_object_del_btn_cancel(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	m->menu.next = LOAD_OBJECT_EDIT;
	(void)m;
	(void)d;
}
