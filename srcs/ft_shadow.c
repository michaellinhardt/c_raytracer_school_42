/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 22:04:03 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/04 16:16:28 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static int	ft_shadow_spot_dir(t_obj *s, t_color *c, t_scene *sc)
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
				coef += (1  - r.obj->eff[0] / 100);
		}
		coef2 += 1;
		s = s->next;
	}
	return ((coef > 0) ? (coef2 - coef) / coef2 : 1);
}

double			ft_shadow(t_obj *s, t_color *c, t_scene *sc)
{
	t_ray	r;
	double	dist[2];
	double	coef;
	double	coef2;

	if (c->spot->type & POINT)
	{
		r.start = new_vector(c->spot_pos.x, c->spot_pos.y, c->spot_pos.z);
		dist[0] = vector_dist(r.start, c->hitpoint);
		r.dir = vector_normalize(vector_sub(c->hitpoint, c->spot_pos));
		coef = 0;
		coef2 = 0;
		while (s)
		{
			if (!s->eff[3])
			{
				dist[1] = lenray(sc, &r);
				if (dist[1] > EPS && dist[1] < dist[0] - EPS)
					coef += (1  - r.obj->eff[0] / 100);
			}
			coef2 += 1;
			s = s->next;
		}
	}
	if (c->spot->type & DIIR)
		return (ft_shadow_spot_dir(s, c, sc));
	return ((coef > 0) ? (coef2 - coef) / coef2 : 1);
}

