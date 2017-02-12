/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_touch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:52:24 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/12 16:21:59 by mlinhard         ###   ########.fr       */
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

static void		lenray_neg(t_obj *obj, t_ray *rayon
	, double *nearest, t_vector *norm)
{
	int		color;
	double	t;
	t_inter inter;

	color = 0;
	while (obj)
	{
		if (obj->eff[3])
		{
			inter.hit1 = -1;
			inter.hit2 = INT_MAX;
			t = lenray_type(rayon, obj, &inter, &color);
			if (t > EPS && inter.hit1 != -1)
				if (nearest[0] == -1 || (inter.hit1 < nearest[0])
					|| inter.hit2 > nearest[1])
				{
					if (nearest[0] == -1 || inter.hit1 < nearest[0])
						nearest[0] = inter.hit1;
					if (nearest[1] == INT_MAX || inter.hit2 > nearest[1])
						nearest[1] = inter.hit2;
					*norm = rayon->norm;
				}
		}
		obj = obj->next;
	}
}

static char		replace_nearest(t_obj *obj, t_ray *rayon,
	double *nearest, t_vector *norm)
{
	if (nearest[3] > nearest[0] && nearest[3] < nearest[1]
		&& nearest[0] > EPS)
	{
		if (nearest[5] < nearest[1] && nearest[4] > nearest[0])
			return (0);
		nearest[2] = nearest[1];
		if ((!(obj->type & COMPLEXE) && (obj->type & PLAN))
			|| (rayon->obj && (!(rayon->obj->type & COMPLEXE)
				&& (rayon->obj->type & PLAN))))
			*norm = vector_rev(*norm);
	}
	else
	{
		nearest[2] = nearest[3];
		*norm = rayon->norm;
	}
	return (1);
}

static t_obj	*lenray_final(t_obj *obj, t_ray *rayon,
	double *n, t_vector *norm)
{
	t_inter		inter;
	int			color;
	t_obj		*tmp_obj;

	color = 0;
	inter.hit1 = -1;
	while (obj)
	{
		if (!obj->eff[3])
		{
			rayon->obj = NULL;
			n[3] = lenray_type(rayon, obj, &inter, &color) - EPS;
			n[4] = inter.hit1;
			n[5] = inter.hit2;
			if ((n[3] < n[2] && n[3] > EPS) || (n[2] < EPS && n[3] > EPS))
				if (replace_nearest(obj, rayon, n, norm))
				{
					tmp_obj = (obj->type != COMPLEXE) ? obj : rayon->obj;
					n[2] = (rayon->dir.y > 0) ? n[2] - EPS : n[2] + EPS;
				}
		}
		obj = obj->next;
	}
	return (tmp_obj);
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
	tmp_obj = lenray_final(sc->obj, rayon, nearest, &norm);
	if (nearest[2] > EPS)
	{
		rayon->norm = norm;
		rayon->obj = tmp_obj;
	}
	return (nearest[2]);
}
