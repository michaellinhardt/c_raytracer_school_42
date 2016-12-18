/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2016/12/18 17:33:06 by ocarta-l         ###   ########.fr       */
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
	t_id		*t;
	t_thread	*mt;
	t_ray		r;
	int			i[2];

	mt = (t_thread*)z;
	r.start = new_vector(mt->s->sc->cam[0],
		mt->s->sc->cam[1], mt->s->sc->cam[2]);
	r.dir = new_vector(mt->s->sc->cam[3], mt->s->sc->cam[4], mt->s->sc->cam[5]);
	tmp = mt->s->sc->obj;
	t = mt->t;
	i[1] = mt->lim[1] - 1;
	while (++i[1] < mt->lim[3])
	{
		i[0] = mt->lim[0] - 1;
		while (++i[0] < mt->lim[2])
			getnearesthit(&r, mt->s, i[0], i[1]);
	}
	return (NULL);
}

static void		merge_chuncks(void *dest, void const *src)
{
	size_t			size;
	size_t			i;

	i = -1;
	size = W_X * W_Y * 3;
	while (++i < size)
	{
		if ((*(unsigned char *)(src)) > 0)
			(*(unsigned char *)(dest)) = (*(unsigned char *)src);
		dest++;
		src++;
	}
	dest -= size;
}

static void		lanch_raytracing(pthread_t *p, t_gen *s, t_id t,
	unsigned char **pixbuffer)
{
	int	j;

	j = -1;
	while (++j < MT)
		pthread_create(&p[j], NULL, display, &t.z[j]);
	j = -1;
	while (++j < MT)
		pthread_join(p[j], NULL);
	*pixbuffer = gdk_pixbuf_get_pixels(s->pixbuf);
	merge_chuncks(*pixbuffer, s->data);
}

void			raytracing(t_gen *s)
{
	static t_id		t;
	static char		c = 0;
	pthread_t		p[MT];
	unsigned char	*pixbuffer;

	s->pixbuf = NULL;
	if (!c)
	{
		(!(t.z = ft_memalloc(sizeof(t_thread) * MT))) ? error(2, "Malloc") : 1;
		init_threads(t.z, &t, s);
		c = 1;
		if (!(s->data = (char *)ft_memalloc(W_X * 3 * W_Y)))
			return ;
	}
	else
		ft_bzero(s->data, W_X * 3 * W_Y);
	if (!(s->pixbuf = gtk_new_image((unsigned char *)(s->data), W_X, W_Y)))
		error(4, "Unable to initialize pixbuf for GtkImage :'(\n");
	lanch_raytracing(p, s, t, &pixbuffer);
	gtk_put_image_to_window(GTK_IMAGE(s->pdrawarea), s->pixbuf);
	free(pixbuffer);
	g_object_unref(s->pixbuf);
}
