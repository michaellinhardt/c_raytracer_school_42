#include "raystruct.h"

void	inter_complex_with_eff(t_ray *r, t_obj *p, int *col, t_complex *c)
{
	c->tmp = p->comp;
	c->nearest[0] = -1;
	c->nearest[1] = INT_MAX;
	while (c->tmp)
	{
		if (c->tmp->eff[3])
		{
			c->i.inter1 = -1;
			c->i.inter2 = INT_MAX;
			c->t = lenray_type(r, c->tmp, &c->i, col);
			if (c->t > EPS && c->i.inter1 != -1)
				if (c->nearest[0] == -1 || (c->i.inter1 < c->nearest[0]) ||
				c->i.inter2 > c->nearest[1])
				{
					if (c->nearest[0] == -1 || c->i.inter1 < c->nearest[0])
						c->nearest[0] = c->i.inter1;
					if (c->nearest[1] == INT_MAX || c->i.inter2 > c->nearest[1])
						c->nearest[1] = c->i.inter2;
					c->norm = r->norm;
				}
		}
		c->tmp = c->tmp->next;
	}
	c->tmp = p->comp;
	c->temp = NULL;
}

double	intersectray_complex(t_ray *r, t_obj *p, int *col)
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
			{
				if (c.t > c.nearest[0] && c.t < c.nearest[1] &&
				c.nearest[0] > 0)
				{
					if (c.i.inter2 <= c.nearest[1] &&
					c.i.inter1 >= c.nearest[0])
					{
						c.tmp = c.tmp->next;
						continue;
					}
					c.new_nearest = c.nearest[1];
					c.temp = c.tmp;
					r->obj = c.tmp;
					c.norm = vector_rev(c.norm);
				}
				else
				{
					c.new_nearest = c.t;
					c.temp = c.tmp;
					r->obj = c.tmp;
					c.norm = r->norm;
				}
			}
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