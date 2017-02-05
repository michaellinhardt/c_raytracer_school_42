/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_filter_call.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:08 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/05 15:36:42 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		menu_filter_call2(t_gen *d, int i)
{
	if (i == 10)
		(FUNC_FILTER_11)(d->sc->data, -4);
	else if (i == 11)
		(FUNC_FILTER_12)(d->sc->data, -4);
	else if (i == 12)
		(FUNC_FILTER_13)(d->sc->data, -4);
	else
		(FUNC_FILTER_14)(d->sc->data, -4);
}

void			menu_filter_call(t_gen *d, int i)
{
	if (i == 0)
		(FUNC_FILTER_1)(d->sc->data, -4);
	else if (i == 1)
		(FUNC_FILTER_2)(d->sc->data, -4);
	else if (i == 2)
		(FUNC_FILTER_3)(d->sc->data, -4);
	else if (i == 3)
		(FUNC_FILTER_4)(d->sc->data, -4);
	else if (i == 4)
		(FUNC_FILTER_5)(d->sc->data, -4);
	else if (i == 5)
		(FUNC_FILTER_6)(d->sc->data, -4);
	else if (i == 6)
		(FUNC_FILTER_7)(d->sc->data, -4);
	else if (i == 7)
		(FUNC_FILTER_8)(d->sc->data, -4);
	else if (i == 8)
		(FUNC_FILTER_9)(d->sc->data, -4);
	else if (i == 9)
		(FUNC_FILTER_10)(d->sc->data, -4);
	else
		menu_filter_call2(d, i);
}
