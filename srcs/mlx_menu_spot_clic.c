/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_spot_clic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:49 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:50 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

void		menu_spot_clic(t_gen *d, t_mlx *m, t_flst *elem)
{
	m->menu.spot = elem->spot;
	m->menu.next = LOAD_SPOT_EDIT;
	menu_edit_mod_btn_open(d, m);
}
