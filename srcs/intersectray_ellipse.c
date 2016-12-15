/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_ellipse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:34:26 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/15 19:34:29 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static double	inter_ellipse(t_ray *r, t_obj *s, t_inter *i, t_ellipse *e)
{
	if (e->second.discriminant < 0)
	{
		e->previous_value1 = i->inter1;
		e->previous_value2 = i->inter2;
		return (0);
	}
	e->second.dist = equa_sec(e->second.a, e->second.b, e->second.discriminant,
	i);
	if (e->second.dist <= 0)
	{
		i->inter1 = e->previous_value1;
		i->inter2 = e->previous_value2;
		return (0);
	}
	e->intersection = get_hitpoint(r->start, r->dir, e->second.dist);
	r->norm = vector_sub(e->intersection, e->pos);
	r->norm.x = 2 * r->norm.x / (s->size[0] * s->size[0]);
	r->norm.y = 2 * r->norm.y / (s->size[1] * s->size[1]);
	r->norm.z = 2 * r->norm.z / (s->size[2] * s->size[2]);
	r->norm = vector_normalize(r->norm);
	return (e->second.dist);
}

double			intersectray_ellipse(t_ray *r, t_obj *s, t_inter *i)
{
	t_ellipse e;

	e.previous_value1 = i->inter1;
	e.previous_value2 = i->inter2;
	e.newpos = new_vector(r->start.x - s->pos[0], r->start.y - s->pos[1],
	r->start.z - s->pos[2]);
	e.pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	e.dir = vector_normalize(new_vector(s->pos[3], s->pos[4], s->pos[5]));
	e.second.a = ((r->dir.x * r->dir.x) / (s->size[0] * s->size[0])) +
	((r->dir.y * r->dir.y) / (s->size[1] * s->size[1])) + ((r->dir.z * r->dir.z)
	/ (s->size[2] * s->size[2]));
	e.second.b = 2 * (((r->dir.x * e.newpos.x) / (s->size[0] * s->size[0])) +
	((r->dir.y * e.newpos.y) / (s->size[1] * s->size[1])) + ((r->dir.z *
	e.newpos.z) / (s->size[2] * s->size[2])));
	e.second.c = ((e.newpos.x * e.newpos.x) / (s->size[0] * s->size[0])) +
	((e.newpos.y * e.newpos.y) / (s->size[1] * s->size[1])) + ((e.newpos.z *
	e.newpos.z) / (s->size[2] * s->size[2])) - 1;
	e.second.discriminant = e.second.b * e.second.b - 4 * (e.second.a
	* e.second.c);
	e.previous_value1 = i->inter1;
	e.previous_value2 = i->inter2;
	return (inter_ellipse(r, s, i, &e));
}
