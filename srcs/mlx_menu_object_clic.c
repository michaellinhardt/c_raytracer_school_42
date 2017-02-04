/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_object_clic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:24 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:25 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

void		menu_object_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	m->menu.obj = elem->obj;
	m->menu.id = LOAD_OBJECT;
	menu_edit_mod_btn_open(d, m);
	(void)d;
}
