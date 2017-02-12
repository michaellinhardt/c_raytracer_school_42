/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2017/02/12 12:18:39 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double			noise(t_ray *r, t_vector hitpoint, double bump_mapping)
{
	double	noisecoef;
	int		level;
	float	n[3];

	noisecoef = 0;
	level = 0;
	while (++level < 50)
	{
		noisecoef += (1.0 / level)
			* fabs((perlin(fabs(level * 0.15 * hitpoint.x),
							fabs(level * 0.15 * hitpoint.y),
							fabs(level * 0.15 * hitpoint.z))));
	}
	noisecoef = (noisecoef > 1.0) ? 1 : noisecoef;
	if (bump_mapping)
	{
		n[0] = perlin(hitpoint.x, hitpoint.y, hitpoint.z);
		n[1] = perlin(hitpoint.y, hitpoint.z, hitpoint.x);
		n[2] = perlin(hitpoint.z, hitpoint.x, hitpoint.y);
		r->norm.x = (1.0f - 0.25) * r->norm.x + 0.25 * n[0];
		r->norm.y = (1.0f - 0.25) * r->norm.y + 0.25 * n[1];
		r->norm.z = (1.0f - 0.25) * r->norm.z + 0.25 * n[2];
		r->norm = vector_normalize(r->norm);
	}
	return (noisecoef);
}

void			*display(void *z)
{
	t_obj		*tmp;
	t_thread	*mt;
	t_ray		r; // <- structure deffinissant un rayon et une normal et le ptr de lobjet
	int			i[2];

	mt = (t_thread*)z;
	r.start = new_vector(mt->s->sc->cam[0], // stoque xyz de la cam dans start
		mt->s->sc->cam[1], mt->s->sc->cam[2]);
	r.dir = new_vector(mt->s->sc->cam[3], mt->s->sc->cam[4], mt->s->sc->cam[5]); // direction de la cam
	tmp = mt->s->sc->obj;
	i[1] = mt->lim[1] - 1;
	while (++i[1] < mt->lim[3])
	{
		// loop de chaque pixel de chaque thread
		i[0] = mt->lim[0] - 1;
		while (++i[0] < mt->lim[2])
			getnearesthit(&r, mt->s, i[0], i[1]);
	}
	return (NULL);
}

static void		lanch_raytracing(pthread_t *p, t_thread *t)
{
	int	j;

	// lance les thread sur la fonction display et join les thread

	j = -1;
	while (++j < MT)
		pthread_create(&p[j], NULL, display, &t[j]);
	j = -1;
	while (++j < MT)
		pthread_join(p[j], NULL);
}

void			raytracing(t_gen *s)
{
	static t_thread	*threads;
	static char		c = 0;
	pthread_t		p[MT];
	int				toto;

	// si c == 0 -> initie les thread et la map, sinon bzero la map

	toto = W_Y * W_X * 4;
	if (!c)
	{
		(!(threads = ft_memalloc(
			sizeof(t_thread) * MT))) ? error(2, "Malloc") : 1;
		init_threads(threads, s);
		c = 1;
		if (!(s->data = (char *)ft_memalloc(toto)))
			return ;
	}
	else
		ft_bzero(s->data, toto);
	lanch_raytracing(p, threads);
}
