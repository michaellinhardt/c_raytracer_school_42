/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_camera_btn_open.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:57 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:57 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_camera_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	d = gen;
	m = mlx;
	m->get[ID_INPUT_CAM1].target.ptr_double = &d->sc->cam[0];
	m->get[ID_INPUT_CAM2].target.ptr_double = &d->sc->cam[1];
	m->get[ID_INPUT_CAM3].target.ptr_double = &d->sc->cam[2];
	m->get[ID_INPUT_CAM4].target.ptr_double = &d->sc->cam[3];
	m->get[ID_INPUT_CAM5].target.ptr_double = &d->sc->cam[4];
	m->get[ID_INPUT_CAM6].target.ptr_double = &d->sc->cam[5];
	m->menu.next = LOAD_CAMERA;
	(void)m;
	(void)gen;
	(void)mlx;
}
