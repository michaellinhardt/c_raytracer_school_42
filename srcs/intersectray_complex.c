/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_complex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 18:54:56 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/16 18:54:59 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void	inter_complex_with_eff(t_ray *r, t_obj *p, int *col, t_complex *c)
{
	c->tmp = p->comp;
	c->nearest[0] = -1;
	c->nearest[1] = INT_MAX;
	while (c->tmp)
	{
		if (c->tmp->eff[3])
		{
			c->i.hit1 = -1;
			c->i.hit2 = INT_MAX;
			c->t = lenray_type(r, c->tmp, &c->i, col);
			if (c->t > EPS && c->i.hit1 != -1)
				if (c->nearest[0] == -1 || (c->i.hit1 < c->nearest[0]) ||
				c->i.hit2 > c->nearest[1])
				{
					if (c->nearest[0] == -1 || c->i.hit1 < c->nearest[0])
						c->nearest[0] = c->i.hit1;
					if (c->nearest[1] == INT_MAX || c->i.hit2 > c->nearest[1])
						c->nearest[1] = c->i.hit2;
					c->norm = r->norm;
				}
		}
		c->tmp = c->tmp->next;
	}
	c->tmp = p->comp;
	c->temp = NULL;
}

static int	inter_complex_with_no_eff(t_ray *r, t_complex *c)
{
	if (c->t > c->nearest[0] && c->t < c->nearest[1] &&
	c->nearest[0] > 0)
	{
		if (c->i.hit2 <= c->nearest[1] &&
		c->i.hit1 >= c->nearest[0])
		{
			c->tmp = c->tmp->next;
			return (1);
		}
		c->new_nearest = c->nearest[1];
		c->temp = c->tmp;
		r->obj = c->tmp;
		c->norm = vector_rev(c->norm);
	}
	else
	{
		c->new_nearest = c->t;
		c->temp = c->tmp;
		r->obj = c->tmp;
		c->norm = r->norm;
	}
	return (0);
}

double		intersectray_complex(t_ray *r, t_obj *p, int *col)
{
	t_complex c;

	inter_complex_with_eff(r, p, col, &c);
	c.new_nearest = -1;
	while (c.tmp)
	{
		if (!c.tmp->eff[3])
		{
			c.t = lenray_type(r, c.tmp, &c.i, col);
			if ((c.t < c.new_nearest && c.t > EPS) ||
			(c.new_nearest < 0 && c.t > EPS))
				if (inter_complex_with_no_eff(r, &c))
					continue;
		}
		c.tmp = c.tmp->next;
	}
	if (c.new_nearest > EPS)
	{
		*col = c.temp->c_o;
		r->norm = c.norm;
	}
	return ((c.new_nearest != -1) ? c.new_nearest : 0);
}
