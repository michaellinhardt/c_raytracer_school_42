/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2017/02/12 12:31:45 by mlinhard         ###   ########.fr       */
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

static void		lanch_raytracing(pthread_t *p, t_thread *thread)
{
	int	j;

	j = -1;
	while (++j < MT)
		pthread_create(&p[j], NULL, raytracing_pixel_loop, &thread[j]);
	j = -1;
	while (++j < MT)
		pthread_join(p[j], NULL);
}

void			raytracing(t_gen *s)
{
	static t_thread	*threads;
	static char		is_init = 0;
	pthread_t		p[MT];
	int				size_data;

	size_data = W_Y * W_X * 4;
	if (!is_init)
	{
		(!(threads = ft_memalloc(
			sizeof(t_thread) * MT))) ? error(2, "Malloc") : 1;
		init_threads(threads, s);
		is_init = 1;
		if (!(s->data = (char *)ft_memalloc(size_data)))
			return ;
	}
	else
		ft_bzero(s->data, size_data);
	lanch_raytracing(p, threads);
}
