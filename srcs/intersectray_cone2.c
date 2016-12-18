/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_cone2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 23:32:10 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/18 23:32:11 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double			inter2_or_plan(t_ray *r, t_obj *s, t_inter *i, t_cone *c)
{
	c->plan_dir = vectormultby_scalar(c->dir, -1);
	c->plan_pos = get_hitpoint(c->pos, c->plan_dir, s->size[0]);
	c->dist_plan = (vector_dot(vector_sub(c->plan_pos, r->start), c->plan_dir) /
	vector_dot(r->dir, c->plan_dir));
	if (c->dist_plan > 0 && i->inter2 > c->dist_plan)
	{
		i->inter1 = c->dist_plan;
		r->norm = c->plan_dir;
		return (c->dist_plan);
	}
	c->inter_pos = get_hitpoint(r->start, r->dir, i->inter2);
	c->lambda = vector_normalize(vector_sub(c->pos, c->inter_pos));
	r->norm = vector_normalize(vector_sub(vectormultby_scalar(c->dir,
	vector_dot(c->lambda, c->dir) / vector_dot(c->dir, c->dir)), c->lambda));
	return (i->inter2);
}

double			inter1_or_plan(t_ray *r, t_obj *s, t_inter *i, t_cone *c)
{
	c->plan_dir = vectormultby_scalar(c->dir, -1);
	c->plan_pos = get_hitpoint(c->pos, c->plan_dir, s->size[0]);
	c->dist_plan = (vector_dot(vector_sub(c->plan_pos, r->start), c->plan_dir) /
	vector_dot(r->dir, c->plan_dir));
	if (c->dist_plan > 0 && i->inter1 > c->dist_plan)
	{
		i->inter2 = i->inter1;
		i->inter1 = c->dist_plan;
		r->norm = c->plan_dir;
		return (c->dist_plan);
	}
	c->inter_pos = get_hitpoint(r->start, r->dir, i->inter1);
	c->lambda = vector_normalize(vector_sub(c->pos, c->inter_pos));
	r->norm = vector_normalize(vector_sub(vectormultby_scalar(c->dir,
	vector_dot(c->lambda, c->dir) / vector_dot(c->dir, c->dir)), c->lambda));
	return (i->inter1);
}

static double	touch_cone(t_ray *r, t_inter *i, t_cone *c)
{
	if (i->inter2 > i->inter1)
	{
		c->inter_pos = get_hitpoint(r->start, r->dir, i->inter2);
		c->lambda = vector_normalize(vector_sub(c->pos, c->inter_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(c->dir,
		vector_dot(c->lambda, c->dir) / vector_dot(c->dir, c->dir)),
		c->lambda));
		i->inter1 = i->inter2;
		i->inter2 = c->dist_plan;
		return (i->inter1);
	}
	else
	{
		c->inter_pos = get_hitpoint(r->start, r->dir, i->inter1);
		c->lambda = vector_normalize(vector_sub(c->pos, c->inter_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(c->dir,
		vector_dot(c->lambda, c->dir) / vector_dot(c->dir, c->dir)),
		c->lambda));
		i->inter2 = c->dist_plan;
		return (i->inter1);
	}
}

double			touch_cone_or_plan(t_ray *r, t_obj *s, t_inter *i, t_cone *c)
{
	c->plan_dir = vectormultby_scalar(c->dir, -1);
	c->plan_pos = get_hitpoint(c->pos, c->plan_dir, s->size[0]);
	c->dist_plan = (vector_dot(vector_sub(c->plan_pos, r->start), c->plan_dir) /
	vector_dot(r->dir, c->plan_dir));
	if (c->dist_plan > 0 && i->inter1 > c->dist_plan && i->inter2 >
	c->dist_plan)
	{
		i->inter2 = i->inter1;
		i->inter1 = c->dist_plan;
		r->norm = c->plan_dir;
		return (c->dist_plan);
	}
	return (touch_cone(r, i, c));
}
