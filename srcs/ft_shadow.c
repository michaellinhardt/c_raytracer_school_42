/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 22:04:03 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/04 17:24:00 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static int		ft_shadow_spot_dir(t_obj *s, t_color *c, t_scene *sc)
{
	t_ray	r;
	double	dist;
	double	coef;
	double	coef2;

	r.start = c->hitpoint;
	r.dir = c->vec_obj_light;
	coef = 0;
	coef2 = 0;
	while (s)
	{
		if (!s->eff[3])
		{
			dist = lenray(sc, &r);
			if (dist > EPS)
				coef += (1 - r.obj->eff[0] / 100);
		}
		coef2 += 1;
		s = s->next;
	}
	return ((coef > 0) ? (coef2 - coef) / coef2 : 1);
}

double			ft_shadow(t_obj *s, t_color *c, t_scene *sc)
{
	t_ray	r;
	double	dist[4];

	if (c->spot->type & POINT)
	{
		r.start = new_vector(c->spot_pos.x, c->spot_pos.y, c->spot_pos.z);
		dist[0] = vector_dist(r.start, c->hitpoint);
		r.dir = vector_normalize(vector_sub(c->hitpoint, c->spot_pos));
		dist[2] = 0;
		dist[3] = 0;
		while (s)
		{
			if (!s->eff[3])
			{
				dist[1] = lenray(sc, &r);
				if (dist[1] > EPS * 20 && dist[1] < dist[0] - EPS * 20)
					dist[2] += (1 - r.obj->eff[0] / 100);
			}
			dist[3] += 1;
			s = s->next;
		}
	}
	if (c->spot->type & DIIR)
		return (ft_shadow_spot_dir(s, c, sc));
	return ((dist[2] > 0) ? (dist[3] - dist[2]) / dist[3] : 1);
}
