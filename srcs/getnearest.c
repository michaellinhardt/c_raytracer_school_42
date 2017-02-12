/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnearest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:22:00 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/12 16:39:39 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			sqrtc(double *color)
{
	color[0] = sqrtf(color[0]);
	color[1] = sqrtf(color[1]);
	color[2] = sqrtf(color[2]);
}

static void		init_cam(t_ray *rayon, t_vector *cam_angle, t_vector pixel)
{
	pixel.x = pixel.x - W_X / 2.0;
	pixel.y = W_Y / 2.0 - pixel.y;
	pixel.z = (W_Y / 2.0) / tan(70 * 0.5);
	rayon->dir = vector_normalize(new_vector(pixel.x, pixel.y, pixel.z));
	if (cam_angle->x)
		rayon->dir = matricerot_x(rayon->dir, cam_angle->x);
	if (cam_angle->y)
		rayon->dir = matricerot_y(rayon->dir, cam_angle->y);
	if (cam_angle->z)
		rayon->dir = matricerot_z(rayon->dir, cam_angle->z);
}

static void		getnearesthit_end(t_ray *r,
	t_gen *raytracer, int *c, double *co)
{
	int		j[2];
	double	e[2];

	j[0] = 0;
	j[1] = c[0];
	e[0] = co[3];
	e[1] = 1;
	c[1] = refraction(raytracer->sc, r, j, e);
}

static void		getnearesthit_mid(t_ray *r,
	t_gen *raytracer, int *c, double *co)
{
	int		i[2];
	double	d[2];

	if (r->obj && (r->obj->type))
	{
		c[0] = diffuse(raytracer->sc, r, co[3], r->obj->c_o);
		if (r->obj->eff[1])
		{
			i[0] = c[0];
			i[1] = 0;
			d[0] = co[3];
			d[1] = r->obj->eff[1];
			c[2] = reflexion(raytracer->sc, r, i, d);
		}
		if (r->obj->eff[2] && r->obj->eff[0])
			getnearesthit_end(r, raytracer, c, co);
	}
	co[1] = r->obj->eff[0] / 100;
	co[0] = r->obj->eff[1] / 100;
	co[2] = 1 - co[0] - co[1];
}

double			getnearesthit(t_ray *ray, t_gen *raytracer, double x, double y)
{
	double	ref[3];
	double	co[4];
	double	d[3];
	double	re[3];
	int		c[3];

	init_cam(ray, &raytracer->view_angle, new_vector(x, y, 0));
	co[3] = lenray(raytracer->sc, ray);
	if (co[3] >= EPS)
	{
		getnearesthit_mid(ray, raytracer, c, co);
		color_composants(c[0], d);
		color_composants(c[1], re);
		color_composants(c[2], ref);
		d[0] = co[0] * ref[0] + co[1] * re[0] + co[2] * d[0];
		d[1] = co[0] * ref[1] + co[1] * re[1] + co[2] * d[1];
		d[2] = co[0] * ref[2] + co[1] * re[2] + co[2] * d[2];
		c[1] = colorfromrgb(d);
		pixel_to_char(raytracer, c[1], x, y);
	}
	return (co[3]);
}
