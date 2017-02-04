/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_btn_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:51 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:52 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_btn_left(void *gen, void *mlx)
{
	t_mlx	*m;

	m = mlx;
	if (m->scene == RT && m->menu.draw == 1)
		menu_load_btn_prev(gen, mlx);
	(void)gen;
	(void)mlx;
}
