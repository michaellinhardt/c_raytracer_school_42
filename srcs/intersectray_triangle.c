#include "raystruct.h"

double intersectray_triangle(t_ray *r, t_obj *p, t_inter *i)
{
	double t;
	double d;
	double near;
	t_obj		*tmp;
	t_vector new;
	t_vector test;
	t_vector c0;
	t_vector c1;
	t_vector c2;
	t_vector c3;
	
	tmp = p->comp;
	near = INT_MAX;
	while (tmp)
	{
		c0 = vector_sub(tmp->tri[1], tmp->tri[0]);
		c1 = vector_sub(tmp->tri[2], tmp->tri[0]);
		test = vector_cross(r->dir, c1);
		d = vector_dot(c0, test);
		if (d > -EPS && d < EPS)
		{
			tmp = tmp->next;
			continue ;
		}
		t = 1.0 / d;
		c2 = vector_sub(r->start, tmp->tri[0]);
		double u = t * vector_dot(c2, test);
		if (u < 0.0 || u > 1.0)
		{
			tmp = tmp->next;
			continue ;	
		}
		c3 = vector_cross(c2, c0);
		double v = t * vector_dot(r->dir, c3);
		if (v < 0.0 || u + v > 1.0)
		{
			tmp = tmp->next;
			continue ;	
		}
		t = t * vector_dot(c1, c3);
		if (t > 0.01 && t < near)
		{
			new = tmp->nor;
			near = t;
		}
		tmp = tmp->next;
	}
	if (near > EPS && near < INT_MAX)
	{
		r->norm = new;
		i->inter1 = near;
		r->norm = vector_normalize(r->norm);
		return (near);
	}
	return (0);
}