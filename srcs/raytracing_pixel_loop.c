/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_pixel_loop.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2017/02/12 12:31:48 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			*raytracing_pixel_loop(void *z)
{
	t_obj		*tmp;
	t_thread	*mt;
	t_ray		r; // <- structure deffinissant un rayon et une normal et le ptr de lobjet
	int			i[2];

	mt = (t_thread*)z;
	r.start = new_vector(mt->s->sc->cam[0], // stoque xyz de la cam dans start
		mt->s->sc->cam[1], mt->s->sc->cam[2]);
	r.dir = new_vector(mt->s->sc->cam[3], mt->s->sc->cam[4], mt->s->sc->cam[5]); // direction de la cam
	tmp = mt->s->sc->obj;
	i[1] = mt->lim[1] - 1;
	while (++i[1] < mt->lim[3])
	{
		// loop de chaque pixel de chaque thread
		i[0] = mt->lim[0] - 1;
		while (++i[0] < mt->lim[2])
			getnearesthit(&r, mt->s, i[0], i[1]);
	}
	return (NULL);
}
