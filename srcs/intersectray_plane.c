/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:24:23 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/19 12:24:25 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double	intersectray_plane(t_ray *r, t_obj *p, t_inter *i)
{
	double		t;
	t_vector	n;
	t_vector	p0;

	p0 = new_vector(p->pos[0], p->pos[1], p->pos[2]);
	n = vector_normalize(new_vector(p->pos[3], p->pos[4], p->pos[5]));
	t = (vector_dot(vector_sub(p0, r->start), n) / vector_dot(r->dir, n));
	if (t > EPS)
	{
		r->norm = n;
		i->inter1 = t;
		i->inter2 = i->inter1;
		r->norm = vector_normalize(r->norm);
		if (p->cut)
			return (cut_object(p, t, r, 0));
		return (t);
	}
	return (0);
}
