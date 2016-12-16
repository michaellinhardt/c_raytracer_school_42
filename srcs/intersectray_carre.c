/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_carre.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:42:47 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/16 16:42:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		find_norm_carre(t_ray *r, t_obj *s, t_carre *c)
{
	r->norm = new_vector(0, 0, 0);
	if (c->calc.x >= s->size[0] / 2)
		r->norm.x = 1;
	else if (c->calc.x <= -s->size[0] / 2)
		r->norm.x = -1;
	if (c->calc.y >= s->size[1] / 2)
		r->norm.y = 1;
	else if (c->calc.y <= -s->size[1] / 2)
		r->norm.y = -1;
	if (c->calc.z >= s->size[2] / 2)
		r->norm.z = 1;
	else if (c->calc.z <= -s->size[2] / 2)
		r->norm.z = -1;
	if (fabs(c->calc.x) >= fabs(c->calc.y) && fabs(c->calc.z) >=
	fabs(c->calc.y))
		r->norm.y = 0;
	else if (fabs(c->calc.x) >= fabs(c->calc.z) &&
	fabs(c->calc.z) <= fabs(c->calc.y))
		r->norm.z = 0;
	else
		r->norm.x = 0;
}

static double	calc_all_t(t_ray *r, t_obj *s, t_carre *c)
{
	c->t_min = (-s->size[0] / 2 - (r->start.x - s->pos[0])) / r->dir.x;
	c->tmax = (s->size[0] / 2 - (r->start.x - s->pos[0])) / r->dir.x;
	if (c->t_min > c->tmax)
	{
		c->t = c->t_min;
		c->t_min = c->tmax;
		c->tmax = c->t;
	}
	c->tymin = (-s->size[1] / 2 - (r->start.y - s->pos[1])) / r->dir.y;
	c->tymax = (s->size[1] / 2 - (r->start.y - s->pos[1])) / r->dir.y;
	if (c->tymin > c->tymax)
	{
		c->t = c->tymin;
		c->tymin = c->tymax;
		c->tymax = c->t;
	}
	if ((c->t_min > c->tymax) || (c->tymin > c->tmax))
		return (0);
	if (c->tymin > c->t_min)
		c->t_min = c->tymin;
	if (c->tymax < c->tmax)
		c->tmax = c->tymax;
	c->tzmin = (-s->size[2] / 2 - (r->start.z - s->pos[2])) / r->dir.z;
	c->tzmax = (s->size[2] / 2 - (r->start.z - s->pos[2])) / r->dir.z;
	return (1);
}

double			intersectray_carre(t_ray *r, t_obj *s, t_inter *i)
{
	t_carre	c;

	if (!calc_all_t(r, s, &c))
		return (0);
	if (c.tzmin > c.tzmax)
	{
		c.t = c.tzmin;
		c.tzmin = c.tzmax;
		c.tzmax = c.t;
	}
	if ((c.t_min > c.tzmax) || (c.tzmin > c.tmax))
		return (0);
	if (c.tzmin > c.t_min)
		c.t_min = c.tzmin;
	if (c.tzmax < c.tmax)
		c.tmax = c.tzmax;
	c.dist = (c.t_min < c.tmax) ? c.t_min : c.tmax;
	i->inter1 = c.dist;
	i->inter2 = (c.t_min > c.tmax) ? c.t_min : c.tmax;
	c.hitpoint = get_hitpoint(r->start, r->dir, c.dist);
	c.rec_pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	c.calc = vector_sub(c.hitpoint, c.rec_pos);
	find_norm_carre(r, s, &c);
	return (c.dist);
}
