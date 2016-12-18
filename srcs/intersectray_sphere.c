/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectray_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 20:08:10 by bbrunell          #+#    #+#             */
/*   Updated: 2016/12/18 12:32:30 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static double	cut_or_not(t_ray *r, t_obj *s, t_sphere *sphere, t_inter *i)
{
	(void)i;
	if (s->cut)
	{
		if (!cut_object(s, sphere->second.dist, r, 0))
		{
			return (0);
			if (sphere->second.dist < ((-sphere->second.b
				+ sqrtf(sphere->second.discriminant))
			/ (2 * sphere->second.a)))
			{
				sphere->second.dist = ((-sphere->second.b
					+ sqrtf(sphere->second.discriminant))
				/ (2 * sphere->second.a));
			}
			else
			{
				sphere->second.dist = ((-sphere->second.b
					- sqrtf(sphere->second.discriminant))
				/ (2 * sphere->second.a));
			}
			r->norm = vector_rev(r->norm);
		}
	}
	return (sphere->second.dist);
}

static double	find_sphere_intersect(t_ray *r, t_obj *s, t_sphere *sphere,
t_inter *i)
{
	sphere->second.dist = ((-sphere->second.b +
	sqrtf(sphere->second.discriminant))
	/ (2 * sphere->second.a));
	if (((-sphere->second.b - sqrtf(sphere->second.discriminant)) /
	(2 * sphere->second.a)) < (sphere->second.dist))
	{
		sphere->second.dist = ((-sphere->second.b -
		sqrtf(sphere->second.discriminant)) / (2 * sphere->second.a));
		i->inter1 = sphere->second.dist;
		i->inter2 = ((-sphere->second.b + sqrtf(sphere->second.discriminant))
		/ (2 * sphere->second.a));
	}
	else
	{
		i->inter1 = ((-sphere->second.b + sqrtf(sphere->second.discriminant))
		/ (2 * sphere->second.a));
		i->inter2 = ((-sphere->second.b - sqrtf(sphere->second.discriminant))
		/ (2 * sphere->second.a));
	}
	sphere->inter = get_hitpoint(r->start, r->dir, sphere->second.dist);
	r->norm = new_vector((sphere->inter.x - s->pos[0]) / s->size[0],
	(sphere->inter.y - s->pos[1]) / s->size[0], (sphere->inter.z - s->pos[2]) /
	s->size[0]);
	r->norm = vector_normalize(r->norm);
	return (cut_or_not(r, s, sphere, i));
}

double			intersectray_sphere(t_ray *r, t_obj *s, t_inter *i)
{
	t_sphere	sphere;

	sphere.pos = new_vector(r->start.x - s->pos[0], r->start.y -
	s->pos[1], r->start.z - s->pos[2]);
	sphere.second.a = vector_dot(r->dir, r->dir);
	sphere.second.b = 2 * vector_dot(r->dir, sphere.pos);
	sphere.second.c = vector_dot(sphere.pos, sphere.pos) -
	s->size[0] * s->size[0];
	sphere.second.discriminant = sphere.second.b * sphere.second.b - 4 *
	(sphere.second.a * sphere.second.c);
	if (sphere.second.discriminant < 0)
		return (0);
	if (((-sphere.second.b + sqrtf(sphere.second.discriminant)) /
	(2 * sphere.second.a)) <= 0 || ((-sphere.second.b -
	sqrtf(sphere.second.discriminant)) / (2 * sphere.second.a)) <= 0)
		return (0);
	return (find_sphere_intersect(r, s, &sphere, i));
}
