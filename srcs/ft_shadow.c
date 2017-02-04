/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 22:04:03 by bbrunell          #+#    #+#             */
/*   Updated: 2017/01/03 15:01:30 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static int	ft_shadow_spot_dir(t_obj *s, t_color *c, t_scene *sc)
{
	t_ray	r;
	double	dist;
	double	coef;

	coef = 1;
	r.start = c->hitpoint;
	r.dir = c->vec_obj_light;
	while (s)
	{
		if (!s->eff[3])
		{
			dist = lenray(sc, &r);
			coef = coef * (r.obj->eff[0] / 100);
		}
		s = s->next;
	}
	coef = (coef > 1) ? 1 : coef;
	return ((coef > 0) ? coef : 0);
}

double			ft_shadow(t_obj *s, t_color *c, t_scene *sc)
{
	t_ray	r;
	double	dist[2];
	double	coef;

	coef = 1;
	if (c->spot->type & POINT)
	{
		r.start = new_vector(c->spot_pos.x, c->spot_pos.y, c->spot_pos.z);
		dist[0] = vector_dist(r.start, c->hitpoint);
		r.dir = vector_normalize(vector_sub(c->hitpoint, c->spot_pos));
		while (s)
		{
			if (!s->eff[3])
			{
				dist[1] = lenray(sc, &r);
				if (dist[1] > EPS && dist[1] < dist[0] - EPS)
					coef = coef * (1 - r.obj->eff[0] / 100);
			}
			s = s->next;
		}
	}
	if (c->spot->type & DIIR)
		return (ft_shadow_spot_dir(s, c, sc));
	coef = (coef > 1) ? 1 : coef;
	return ((coef < 0) ? 0 : coef);
}