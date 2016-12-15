/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_touch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:52:24 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/19 05:30:49 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double			lenray_type(t_ray *r, t_obj *s, t_inter *i, int *col)
{
	if (s->type & SPHERE)
		return (intersectray_sphere(r, s, i));
	else if (s->type & PLAN)
		return (intersectray_plane(r, s, i));
	else if (s->type & CYLINDRE)
		return (intersectray_cylindre(r, s, i));
	else if (s->type & RECTANGLE)
		return (intersectray_carre(r, s, i));
	else if (s->type & COMPLEXE)
		return (intersectray_complex(r, s, col));
	else if (s->type & CONE)
		return (intersectray_cone(r, s, i));
	else if (s->type & BOLOID)
		return (intersectray_boloid(r, s, i));
	else if (s->type & TRIANGLE)
		return (intersectray_triangle(r, s, i));
	else if (s->type & ELLIPSE)
		return (intersectray_ellipse(r, s, i));
	return (0);
}

static void		lenray_neg(t_obj *s, t_ray *r, double *nearest, t_vector *norm)
{
	int		color;
	double	t;
	t_inter i;

	color = 0;
	while (s)
	{
		if (s->eff[3])
		{
			i.inter1 = -1;
			i.inter2 = INT_MAX;
			t = lenray_type(r, s, &i, &color);
			if (t > EPS && i.inter1 != -1)
				if (nearest[0] == -1 || (i.inter1 < nearest[0])
					|| i.inter2 > nearest[1])
				{
					if (nearest[0] == -1 || i.inter1 < nearest[0])
						nearest[0] = i.inter1;
					if (nearest[1] == INT_MAX || i.inter2 > nearest[1])
						nearest[1] = i.inter2;
					*norm = r->norm;
				}
		}
		s = s->next;
	}
}

static char		replace_nearest(t_obj *s, t_ray *r,
	double *nearest, t_vector *norm)
{
	if (nearest[3] > nearest[0] && nearest[3] < nearest[1]
		&& nearest[0] > EPS)
	{
		if (nearest[5] < nearest[1] && nearest[4] > nearest[0])
			return (0);
		nearest[2] = nearest[1];
		if ((!(s->type & COMPLEXE) && (s->type & PLAN))
			|| (r->obj && (!(r->obj->type & COMPLEXE) && (r->obj->type & PLAN))))
			*norm = vector_rev(*norm);
	}
	else
	{
		nearest[2] = nearest[3];
		*norm = r->norm;
	}

	return (1);
}

static t_obj	*lenray_final(t_obj *s, t_ray *r,
	double *nearest, t_vector *norm)
{
	t_inter		i;
	int			color;
	t_obj		*tmp;

	color = 0;
	i.inter1 = -1;
	while (s)
	{
		if (!s->eff[3])
		{
			r->obj = NULL;
			nearest[3] = lenray_type(r, s, &i, &color);
			// if (r->dir.x < 0 || r->dir.y > 0)
				nearest[3] -= EPS;
			// else
				// nearest[3] += EPS;	
			nearest[4] = i.inter1;
			nearest[5] = i.inter2;
			if ((nearest[3] < nearest[2] && nearest[3] > EPS)
				|| (nearest[2] < EPS && nearest[3] > EPS))
			{
				if (replace_nearest(s, r, nearest, norm))
				{
					tmp = (s->type != COMPLEXE) ? s : r->obj;
					if (r->dir.y > 0)
						nearest[2] -= EPS;
					else
						nearest[2] += EPS;
				}
			}
		}
		s = s->next;
	}
	return (tmp);
}

double			lenray(t_scene *sc, t_ray *r)
{
	double		nearest[6];
	t_obj		*tmp;
	t_vector	norm;

	tmp = NULL;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	norm.x = 0;
	lenray_neg(sc->obj, r, nearest, &norm);
	nearest[2] = -1;
	tmp = lenray_final(sc->obj, r, nearest, &norm);
	if (nearest[2] > EPS)
	{
		r->norm = norm;
		r->obj = tmp;
	}
	return (nearest[2]);
}
