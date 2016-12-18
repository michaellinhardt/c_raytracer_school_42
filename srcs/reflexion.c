/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:20:09 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 17:21:08 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

int				texture_sphere(t_obj *tmp, t_vector hitpoint)
{
	t_vector	vn[3];
	double		phi[2];
	double		v;
	double		u;

	vn[0] = (new_vector(0, -1, 0));
	vn[1] = (new_vector(1, 0, 0));
	vn[2] = vector_normalize(vector_sub(hitpoint,
		new_vector(tmp->pos[0], tmp->pos[1], tmp->pos[2])));
	phi[0] = acosf(-vector_dot(vector_normalize(vn[0]),
		vector_normalize(vn[2])));
	v = phi[0] / M_PI;
	phi[1] = acosf(vector_dot(vector_normalize(vn[2]),
		vector_normalize(vn[1])) / (sinf(phi[0]))) / (8 * M_PI);
	u = (vector_dot(vector_cross(vn[0], vn[1]), hitpoint) > 0) ?
	phi[1] : 1 - phi[1];
	if (tmp->text & EARTH)
		return (texture_earth(u, v, NULL, NULL));
	else if (tmp->text & FIRE)
		return (texture_fire(u, v, NULL, NULL));
	else if (tmp->text & BLACK)
		return (texture_black(u, v, NULL, NULL));
	else if (tmp->text & ICE)
		return (texture_ice(u, v, NULL, NULL));
	return (0);
}

int				texture(t_obj *tmp, t_vector hitpoint)
{
	if (tmp->type & SPHERE)
		return (texture_sphere(tmp, hitpoint));
	return (0);
}

static void		reflexion_mid(t_reflex *w, int *i, double *d, t_scene *sc)
{
	w->n[2] = d[1] / 100;
	w->n[3] = w->nw.obj->eff[0] / 100;
	w->n[1] = 1 - w->n[3] - w->n[2];
	if (w->n[1] < 0)
	{
		w->n[1] = 0;
		w->n[3] = w->n[3] / (w->n[2] + w->n[3]);
		w->n[2] = w->n[2] / (w->n[2] + w->n[3]);
	}
	w->r[0] = w->r[0] * (1 - w->n[2]) + w->t_rgb[0] * w->n[2];
	w->r[1] = w->r[1] * (1 - w->n[2]) + w->t_rgb[1] * w->n[2];
	w->r[2] = w->r[2] * (1 - w->n[2]) + w->t_rgb[2] * w->n[2];
	w->r[0] = w->n[1] * w->r[0] + w->n[2] * w->t_rgb[0] + w->n[3] * w->r_rgb[0];
	w->r[1] = w->n[1] * w->r[1] + w->n[2] * w->t_rgb[1] + w->n[3] * w->r_rgb[1];
	w->r[2] = w->n[1] * w->r[2] + w->n[2] * w->t_rgb[2] + w->n[3] * w->r_rgb[2];
	i[0] = colorfromrgb(w->r);
	if (w->nw.obj->eff[1])
	{
		i[1] = i[1] + 1;
		d[0] = w->n[0];
		d[1] = w->nw.obj->eff[1];
		i[0] = reflexion(sc, &w->nw, i, d);
	}
}

static void		reflexion_first(t_reflex *w, int *i, double *d, t_scene *sc)
{
	if (w->nw.obj && (w->nw.obj->type))
		w->c[0] = diffuse(sc, &w->nw, w->n[0], w->nw.obj->c_o);
	if (w->nw.obj->eff[0] && w->nw.obj->eff[2])
	{
		w->j[0] = 0;
		w->j[1] = w->c[0];
		w->e[0] = w->n[0];
		w->e[1] = 1;
		w->c[1] = refraction(sc, &w->nw, w->j, w->e);
	}
	color_composants(w->c[0], w->t_rgb);
	color_composants(i[0], w->r);
	color_composants(w->c[1], w->r_rgb);
	reflexion_mid(w, i, d, sc);
}

int				reflexion(t_scene *sc, t_ray *r, int *i, double *d)
{
	t_reflex re;

	re.nw.start = get_hitpoint(r->start, r->dir, d[0]);
	re.nw.dir = vector_dir(r->dir, vectormultby_scalar(r->norm,
		vector_dot(r->norm, r->dir) * 2));
	re.n[0] = lenray(sc, &re.nw);
	re.c[0] = 0;
	re.c[1] = 0;
	if (i[1] < 15 && re.n[0] > EPS && re.nw.obj)
		reflexion_first(&re, i, d, sc);
	else if (re.n[0] <= 0)
	{
		color_composants(i[0], re.t_rgb);
		re.t_rgb[0] = re.t_rgb[0] * (re.n[2]);
		re.t_rgb[1] = re.t_rgb[1] * (re.n[2]);
		re.t_rgb[2] = re.t_rgb[2] * (re.n[2]);
		i[0] = colorfromrgb(re.t_rgb);
	}
	return (i[0]);
}
