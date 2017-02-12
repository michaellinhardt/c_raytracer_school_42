/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2017/02/12 12:46:26 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		*raytracing_pixel_loop(void *ptr_thread)
{
	t_thread	*thread;
	t_ray		rayon;
	t_scene		*sc;
	int			i[2];

	thread = (t_thread *)ptr_thread;
	sc = thread->s->sc;
	rayon.start = new_vector(sc->cam[0], sc->cam[1], sc->cam[2]);
	rayon.dir = new_vector(sc->cam[3], sc->cam[4] , sc->cam[5]);
	i[1] = thread->lim[1] - 1;
	while (++i[1] < thread->lim[3])
	{
		i[0] = thread->lim[0] - 1;
		while (++i[0] < thread->lim[2])
			getnearesthit(&rayon, thread->s, i[0], i[1]);
	}
	return (NULL);
}

static void		raytracing_lanch_thread(pthread_t *p, t_thread *thread)
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
	raytracing_lanch_thread(p, threads);
}
