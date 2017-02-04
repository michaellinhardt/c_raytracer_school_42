/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:01 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:01 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

void			mouse_release(t_gen *d, int btn, int x, int y)
{
	if (mouse_release_get(d, btn, x, y))
		return ;
	else if (btn == 1 && mouse_release_flst(d, d->mlx.flst, x, y))
		return ;
	else if (mouse_release_img(d, btn, x, y))
		return ;
}
