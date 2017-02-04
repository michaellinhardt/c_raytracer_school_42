/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:39:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/01/03 15:01:22 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		diffuse_shadow_specular_end(t_color *c,
	t_ray *r, double *speculaire, double *obj_dotn)
{
	c->dot_light_norm = (c->dot_light_norm > 0 && c->dot_light_norm <= 90)
	? c->dot_light_norm : 0;
	c->mirror_vec_light = vector_normalize(vector_sub(vectormultby_scalar(
	r->norm, 2 * vector_dot(r->norm, c->vec_obj_light)), c->vec_obj_light));
	*obj_dotn = vector_dot(r->norm, c->vec_obj_light);
	c->i_l[c->i] = (*obj_dotn > 0 && *obj_dotn <= 90) ? c->i_l[c->i] : 0;
	*speculaire = vector_dot(c->mirror_vec_light, c->vec_obj_eye);
	*speculaire = (*speculaire > 0 && *speculaire <= 90) ? *speculaire : 0;
	if (c->spot->type & DIIR)
		speculaire = 0;
}

static double	diffuse_shadow_specular(t_ray *r, t_color *c, t_scene *sc,
t_obj *tmp)
{
	double speculaire;
	double obj_dotn;

	speculaire = 1;
	c->spot_pos = new_vector(c->spot->pos[0], c->spot->pos[1],
	c->spot->pos[2]);
	color_composants(c->spot->c_s, c->i_l);
	if (c->spot->type & POINT)
		c->vec_obj_light = vector_dir(c->spot_pos, c->hitpoint);
	else if (c->spot->type & DIIR)
		c->vec_obj_light = vectormultby_scalar(vector_normalize(
			new_vector(c->spot->pos[3], c->spot->pos[4], c->spot->pos[5])), -1);
	c->dot_light_norm = vector_dot(c->vec_obj_light, r->norm);
	c->i_l[c->i] = ft_shadow(sc->obj, c, sc) * c->i_l[c->i];
	c->i_l[c->i] = (c->i_l[c->i] < 0) ? 0 : c->i_l[c->i];
	if (vector_dot(r->norm, vectormultby_scalar(c->vec_obj_light, -1)) > 0 &&
	tmp->type == PLAN)
		return (0);
	diffuse_shadow_specular_end(c, r, &speculaire, &obj_dotn);
	return ((c->i_l[c->i] == 0) ? 0 : c->i_l[c->i] * (c->rgb[c->i] *
	c->dot_light_norm + 1 * pow(speculaire, 66)));
}

static void		diffuse_end(t_ray *r, t_obj *tmp, t_color *c, t_scene *sc)
{
	while (++c->i < 3)
	{
		c->spot = sc->spot;
		c->col = 0;
		while (c->spot)
		{
			c->col = c->col + diffuse_shadow_specular(r, c, sc, tmp);
			c->spot = c->spot->next;
		}
		c->intensity[c->i] = sc->amb[1] * c->rgb[c->i] * c->i_a[c->i] + c->col;
	}
}

int				diffuse(t_scene *sc, t_ray *r, double nearest, int col)
{
	t_color	c;
	t_obj	*tmp;

	tmp = r->obj;
	c.hitpoint = get_hitpoint(r->start, r->dir, nearest);
	if (!(tmp->type & COMPLEXE))
		color_composants((!(tmp->text)) ? tmp->c_o
			: texture(tmp, c.hitpoint), c.rgb);
	else
		color_composants(col, c.rgb);
	color_composants(sc->amb[0], c.i_a);
	c.vec_obj_eye = vector_normalize(vector_sub(r->start, c.hitpoint));
	if (tmp->type == PLAN && vector_dot(c.vec_obj_eye, r->norm) < 0)
		r->norm = vectormultby_scalar(r->norm, -1);
	c.i = -1;
	c.spot = sc->spot;
	diffuse_end(r, tmp, &c, sc);
	if (tmp->eff[4])
		color_normalize(c.intensity, c.intensity,
			noise(r, c.hitpoint, tmp->eff[5]), 0);
	return (colorfromrgb(c.intensity));
}
