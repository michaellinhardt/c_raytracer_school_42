/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_edit_add_btn_open.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:00 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:00 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_edit_add_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->menu.id >= LOAD_SCENE && m->menu.id < LOAD_OBJECT)
		m->menu.next = LOAD_SCENE_ADD;
	else if (m->menu.id >= LOAD_OBJECT && m->menu.id < LOAD_SPOT)
		m->menu.next = LOAD_OBJECT_ADD;
	else if (m->menu.id >= LOAD_SPOT && m->menu.id < LOAD_CAMERA)
		m->menu.next = LOAD_SPOT_ADD;
	(void)gen;
	(void)mlx;
}
