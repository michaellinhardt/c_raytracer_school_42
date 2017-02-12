/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_boloid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:27:28 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/15 18:27:29 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static double	inter_boloid(t_ray *r, t_obj *s, t_inter *i, t_boloid *para)
{
	if (para->second.dist < 0)
	{
		i->hit1 = para->previous_value1;
		i->hit2 = para->previous_value2;
		return (0);
	}
	para->intersection = get_hitpoint(r->start, r->dir, para->second.dist);
	para->x = vector_sub(para->intersection, para->pos);
	para->m = vector_dot(r->dir, para->dir) * para->second.dist +
	vector_dot(para->x, para->dir);
	r->norm = vector_sub(para->x, vectormultby_scalar(para->dir, para->m
	+ s->size[0]));
	r->norm = vector_normalize(r->norm);
	return (para->second.dist);
}

double			intersectray_boloid(t_ray *r, t_obj *s, t_inter *i)
{
	t_boloid para;

	para.pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	para.dir = vector_normalize(new_vector(s->pos[3], s->pos[4], s->pos[5]));
	para.x = vector_sub(r->start, para.pos);
	para.second.a = vector_dot(r->dir, r->dir) - vector_dot(r->dir,
	para.dir) * vector_dot(r->dir, para.dir);
	para.second.b = 2 * (vector_dot(r->dir, para.x) - vector_dot(r->dir,
	para.dir) * (vector_dot(para.x, para.dir) + 2 * s->size[0]));
	para.second.c = vector_dot(para.x, para.x) - vector_dot(para.x,
	para.dir) * (vector_dot(para.x, para.dir) + 4 * s->size[0]);
	para.second.discriminant = para.second.b *
	para.second.b - 4 * (para.second.a * para.second.c);
	if (para.second.discriminant < 0)
		return (0);
	para.previous_value1 = i->hit1;
	para.previous_value2 = i->hit2;
	para.second.dist = equa_sec(para.second.a,
	para.second.b, para.second.discriminant, i);
	return (inter_boloid(r, s, i, &para));
}
