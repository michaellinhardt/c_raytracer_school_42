/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_touch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:52:24 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/12 14:33:37 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double			lenray_type(t_ray *rayon, t_obj *obj, t_inter *inter, int *col)
{
	if (obj->type & SPHERE)
		return (intersectray_sphere(rayon, obj, inter));
	else if (obj->type & PLAN)
		return (intersectray_plane(rayon, obj, inter));
	else if (obj->type & CYLINDRE)
		return (intersectray_cylindre(rayon, obj, inter));
	else if (obj->type & RECTANGLE)
		return (intersectray_carre(rayon, obj, inter));
	else if (obj->type & COMPLEXE)
		return (intersectray_complex(rayon, obj, col));
	else if (obj->type & CONE)
		return (intersectray_cone(rayon, obj, inter));
	else if (obj->type & BOLOID)
		return (intersectray_boloid(rayon, obj, inter));
	else if (obj->type & TRIANGLE)
		return (intersectray_triangle(rayon, obj, inter));
	else if (obj->type & ELLIPSE)
		return (intersectray_ellipse(rayon, obj, inter));
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
			|| (r->obj && (!(r->obj->type & COMPLEXE)
				&& (r->obj->type & PLAN))))
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
	double *n, t_vector *norm)
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
			n[3] = lenray_type(r, s, &i, &color) - EPS;
			n[4] = i.inter1;
			n[5] = i.inter2;
			if ((n[3] < n[2] && n[3] > EPS) || (n[2] < EPS && n[3] > EPS))
				if (replace_nearest(s, r, n, norm))
				{
					tmp = (s->type != COMPLEXE) ? s : r->obj;
					n[2] = (r->dir.y > 0) ? n[2] - EPS : n[2] + EPS;
				}
		}
		s = s->next;
	}
	return (tmp);
}

double			lenray(t_scene *sc, t_ray *rayon)
{
	double		nearest[6];
	t_obj		*tmp_obj;
	t_vector	norm;

	tmp_obj = NULL;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	norm.x = 0;
	lenray_neg(sc->obj, rayon, nearest, &norm);
	nearest[2] = -1;
	// sort lobjet le plus proche
	tmp_obj = lenray_final(sc->obj, rayon, nearest, &norm);
	// si lobjet le plus proche est superieur a la distance minimum on le save
	if (nearest[2] > EPS)
	{
		rayon->norm = norm;
		rayon->obj = tmp_obj;
	}
	return (nearest[2]);
}
