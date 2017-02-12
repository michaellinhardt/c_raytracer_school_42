/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2017/02/12 13:58:51 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		init_threads(t_thread *thread, t_gen *s)
{
	int i;
	int j;
	int k;

	i = 0;
	j = W_X / sqrt(MT);
	k = W_Y / sqrt(MT);
	while (i < MT)
	{
		thread[i].nb = i;
		thread[i].lim[0] = i % (int)sqrt(MT) * j;
		thread[i].lim[1] = (int)(i / sqrt(MT)) * k;
		thread[i].lim[2] = i % (int)sqrt(MT) * j + j;
		thread[i].lim[3] = (int)(i / sqrt(MT)) * k + k;
		thread[i].s = s;
		++i;
	}
}

static void		*raytracing_pixel_loop(void *ptr_thread)
{
	t_thread	*thread;
	t_ray		rayon;
	t_scene		*scene;
	int			i[2];

	thread = (t_thread *)ptr_thread;
	scene = thread->s->sc;
	rayon.start = new_vector(scene->cam[0], scene->cam[1], scene->cam[2]);
	rayon.dir = new_vector(scene->cam[3], scene->cam[4] , scene->cam[5]);
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
		if (!(threads = ft_memalloc(sizeof(t_thread) * MT)))
			error(2, "ft_memalloc(t_thread[MT])");
		init_threads(threads, s);
		is_init = 1;
		if (!(s->data = (char *)ft_memalloc(size_data)))
			return ;
	}
	else
		ft_bzero(s->data, size_data);
	raytracing_lanch_thread(p, threads);
}
