/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:46:31 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 17:59:37 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void				refrac_mid(t_refra *w, t_scene *sc, int *j, t_ray *r)
{
	w->co[1] = w->nw.obj->eff[1] / 100;
	w->co[0] = r->obj->eff[0] / 100;
	w->co[2] = 1 - w->co[0] - w->co[1];
	w->color = diffuse(sc, &w->nw, w->nn, w->nw.obj->c_o);
	if (w->nw.obj->eff[1])
	{
		w->i[0] = j[0];
		w->i[1] = 0;
		w->d[0] = w->nn;
		w->d[1] = w->nw.obj->eff[1];
		w->ref = reflexion(sc, &w->nw, w->i, w->d);
	}
	color_composants(w->color, w->t_r);
	color_composants(j[0], w->r);
	color_composants(w->ref, w->r_rb);
	w->r[0] = w->r[0] * (w->co[0]) + w->t_r[0] * (1 - w->co[0]);
	w->r[1] = w->r[1] * (w->co[0]) + w->t_r[1] * (1 - w->co[0]);
	w->r[2] = w->r[2] * (w->co[0]) + w->t_r[2] * (1 - w->co[0]);
	w->r[0] = w->r[0] * w->co[2] + w->t_r[0] * w->co[0] + w->r_rb[0] * w->co[1];
	w->r[1] = w->r[1] * w->co[2] + w->t_r[1] * w->co[0] + w->r_rb[1] * w->co[1];
	w->r[2] = w->r[2] * w->co[2] + w->t_r[2] * w->co[0] + w->r_rb[2] * w->co[1];
	w->color = colorfromrgb(w->r);
	w->nw.norm = vectormultby_scalar(r->norm, -1);
}

static void				refrac_first(t_refra *w,
	t_scene *sc, t_ray *r, double *e)
{
	w->ref = 0;
	w->rf = r->obj->eff[2];
	w->nw.start = get_hitpoint(r->start, r->dir, e[0]);
	r->dir = vectormultby_scalar(r->dir, -1);
	w->ndoti = vector_dot(r->dir, r->norm);
	w->ndot = w->ndoti * w->ndoti;
	w->b = (w->ndoti > 0) ? e[1] / w->rf : w->rf / e[1];
	w->b2 = w->b * w->b;
	w->d2 = 1 - w->b2 * (1 - w->ndot);
	if (w->d2 > 0)
	{
		w->a = (w->ndoti >= 0) ? w->b * w->ndoti - sqrtf(w->d2)
		: w->b * w->ndoti + sqrtf(w->d2);
		w->nw.dir = vector_sub(vectormultby_scalar(r->norm, w->a),
			vectormultby_scalar(r->dir, w->b));
	}
	else
	{
		w->two = w->ndoti + w->ndoti;
		w->nw.dir = vector_sub(vectormultby_scalar(r->norm, w->two), r->dir);
	}
	w->tmp = new_vector(w->nw.dir.x * EPS,
		w->nw.dir.y * EPS, w->nw.dir.z * EPS);
	w->nw.start = vector_add(w->nw.start, w->tmp);
	w->nn = lenray(sc, &w->nw);
}

int						refraction(t_scene *sc, t_ray *r, int *j, double *e)
{
	t_refra	re;

	re.color = 0;
	re.co[0] = 0;
	re.co[1] = 0;
	re.co[2] = 0;
	refrac_first(&re, sc, r, e);
	if (re.nn > EPS)
	{
		refrac_mid(&re, sc, j, r);
		re.rf = (r->obj->name != re.nw.obj->name) ? 1 : re.rf;
		if (re.nw.obj->eff[2] && re.nw.obj->eff[0])
		{
			j[0] = re.color;
			j[1] = j[1] + 1;
			e[0] = re.nn;
			e[1] = re.rf;
			re.color = refraction(sc, &re.nw, j, e);
		}
	}
	return (re.color);
}
