#include "raystruct.h"

double	intersectray_triangle(t_ray *r, t_obj *p, t_inter *i)
{
	t_triangle	tr;	
	
	tr.tmp = p->comp;
	tr.near = INT_MAX;
	while (tr.tmp)
	{
		tr.c0 = vector_sub(tr.tmp->tri[1], tr.tmp->tri[0]);
		tr.c1 = vector_sub(tr.tmp->tri[2], tr.tmp->tri[0]);
		tr.test = vector_cross(r->dir, tr.c1);
		tr.d = vector_dot(tr.c0, tr.test);
		if (tr.d > -EPS && tr.d < EPS)
		{
			tr.tmp = tr.tmp->next;
			continue ;
		}
		tr.t = 1.0 / tr.d;
		tr.c2 = vector_sub(r->start, tr.tmp->tri[0]);
		tr.u = tr.t * vector_dot(tr.c2, tr.test);
		if (tr.u < 0.0 || tr.u > 1.0)
		{
			tr.tmp = tr.tmp->next;
			continue ;	
		}
		tr.c3 = vector_cross(tr.c2, tr.c0);
		tr.v = tr.t * vector_dot(r->dir, tr.c3);
		if (tr.v < 0.0 || tr.u + tr.v > 1.0)
		{
			tr.tmp = tr.tmp->next;
			continue ;	
		}
		tr.t = tr.t * vector_dot(tr.c1, tr.c3);
		if (tr.t > 0.01 && tr.t < tr.near)
		{
			tr.new_norm = tr.tmp->nor;
			tr.near = tr.t;
		}
		tr.tmp = tr.tmp->next;
	}
	if (tr.near > EPS && tr.near < INT_MAX)
	{
		r->norm = tr.new_norm;
		i->inter1 = tr.near;
		r->norm = vector_normalize(r->norm);
		return (tr.near);
	}
	return (0);
}