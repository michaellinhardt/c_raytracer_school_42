/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:46:31 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 16:19:17 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

int		refraction(t_scene *sc, t_ray *r, int *j, double *e)
{
	t_ray		newray;
	t_vector	tmp;
	int			color;
	int			reflcolor;
	double		refrhit;
	double		ndoti;
	double		two_ndoti;
	double		ndoti2;
	double		new_nearest;
	double		refl_rgb[3];
	double		tmp_rgb[3];
	double		rgb[3];
	double		coefftransp = 0;
	double		coeffreflex = 0;
	double		coeffnone = 0;
	int			i[2];
	double		d[2];
	double a, b, b2, d2;

	color = 0;
	coefftransp = 0;
	coeffreflex = 0;
	coeffnone = 0;
	reflcolor = 0;
	refrhit = r->obj->eff[2];
	newray.start = get_hitpoint(r->start, r->dir, e[0]);
	r->dir = vectormultby_scalar(r->dir, -1);
	ndoti = vector_dot(r->dir, r->norm);
	ndoti2 = ndoti * ndoti;
	if (ndoti > 0)
	{
		b = e[1] / refrhit;
		b2 = b * b;
	}
	else 
	{
		b = refrhit / e[1];
		b2 = b * b;
	}
	d2 = 1 - b2 * (1 - ndoti2);
	if (d2 > 0)
	{
		if (ndoti >= 0)
			a = b * ndoti - sqrtf(d2);
		else
			a = b * ndoti + sqrtf(d2);
		newray.dir = vector_sub(vectormultby_scalar(r->norm, a), vectormultby_scalar(r->dir, b));
	}
	else
	{
		two_ndoti = ndoti + ndoti;
		newray.dir = vector_sub(vectormultby_scalar(r->norm, two_ndoti), r->dir);
	}
	tmp = new_vector(newray.dir.x * EPS, newray.dir.y * EPS, newray.dir.z * EPS);
	newray.start = vector_add(newray.start, tmp);
	new_nearest = lenray(sc, &newray);
	if (new_nearest > EPS)
	{
		coeffreflex = newray.obj->eff[1] / 100;
		coefftransp = r->obj->eff[0] / 100;
		coeffnone = 1 - coefftransp - coeffreflex;
		color = diffuse(sc, &newray, new_nearest, newray.obj->c_o);
		if (newray.obj->eff[1])
		{
			i[0] = j[0];
			i[1] = 0;
			d[0] = new_nearest;
			d[1] = newray.obj->eff[1];
			reflcolor = reflexion(sc, &newray, i, d);
		}
		color_composants(color, tmp_rgb);
		color_composants(j[0], rgb);
		color_composants(reflcolor, refl_rgb);
		rgb[0] = rgb[0] * (coefftransp) + tmp_rgb[0] * (1 - coefftransp);
		rgb[1] = rgb[1] * (coefftransp) + tmp_rgb[1] * (1 - coefftransp);
		rgb[2] = rgb[2] * (coefftransp) + tmp_rgb[2] * (1 - coefftransp);
		rgb[0] = rgb[0] * coeffnone + tmp_rgb[0] * coefftransp + refl_rgb[0] * coeffreflex;
		rgb[1] = rgb[1] * coeffnone + tmp_rgb[1] * coefftransp + refl_rgb[1] * coeffreflex;
		rgb[2] = rgb[2] * coeffnone + tmp_rgb[2] * coefftransp + refl_rgb[2] * coeffreflex;
		color = colorfromrgb(rgb);
		newray.norm = vectormultby_scalar(r->norm, -1);
		if (r->obj->name != newray.obj->name)
			refrhit = 1;
		if (newray.obj->eff[2] && newray.obj->eff[0])
		{
			j[0] = color;
			j[1] = j[1] + 1;
			e[0] = new_nearest;
			e[1] = refrhit;
			color = refraction(sc, &newray, j, e);
		}
	}
	return (color);
}
