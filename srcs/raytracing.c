/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2016/08/11 02:50:03 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"
#include <gui.h>

double noise(t_vector hitpoint)
{
	double noiseCoef;
	int level;

	noiseCoef = 0;
	level = 1;
	while (level < 50)
    {
        noiseCoef += (1.0 / level)  
            * fabs((perlin(fabs(level * 0.05 * hitpoint.x),
            	fabs(level * 0.05 * hitpoint.y),
            	fabs(level * 0.05 * hitpoint.z))));
    	level++;
    }
    if (noiseCoef > 1.0)
    	noiseCoef = 1;
    return (noiseCoef);
}

void sqrtc(double *color)
{
	color[0] = sqrtf(color[0]);
	color[1] = sqrtf(color[1]);
	color[2] = sqrtf(color[2]);
}

int diffuse(t_scene *sc, t_ray *r, t_obj *tmp, double nearest, int col)
{
	t_spot		*spot;
	t_vector	hitpoint;
	t_vector	light_dist;
	t_vector	spot_pos;
	double		factor;
	double		is_ob;
	double		rgb[3];
	double		tmp_rgb[3];
	double		total_rgb[3];
	int			nb_spot;

	spot = sc->spot;
	hitpoint = get_hitpoint(r->start, r->dir, nearest);
	nb_spot = 0;
	while (spot)
	{
		spot = spot->next;
		++nb_spot;
	}
	spot = sc->spot;
	if (tmp->type != COMPLEXE)
		color_composants(tmp->c_o, rgb);
	else
		color_composants(col, rgb);
	is_ob = cast_shadow(sc->obj, hitpoint, spot, sc->obj);
	// is_ob = 1;
	ft_bzero(total_rgb, sizeof(double) * 3);
	if (is_ob)
		while (spot)
		{
			spot_pos = new_vector(spot->pos[0], spot->pos[1], spot->pos[2]);
			light_dist = vector_dir(spot_pos, hitpoint);
			factor = vector_dot(light_dist, r->norm);
			color_composants(spot->c_s, tmp_rgb);
			if (factor < 0)
				factor = 0;
			if (factor > 0)
				color_normalize(total_rgb, tmp_rgb, factor, 1);			
			spot = spot->next;
		}
	total_rgb[0] /= nb_spot;
	total_rgb[1] /= nb_spot;
	total_rgb[2] /= nb_spot;
	sqrtc(total_rgb);
	color_normalize(rgb, total_rgb, is_ob /** noise(hitpoint)*/, 0);
	return (colorfromrgb(rgb));
}

int 	reflexion(t_scene *sc, t_ray *r, double m, int col, int ret, double eff)
{
	t_ray	newray;
	int		color;
	double	tmp_rgb[3];
	double	rgb[3];
	double new_nearest;

	newray.start = get_hitpoint(r->start, r->dir, m);
	newray.dir = vector_dir(r->dir, vectormultby_scalar(r->norm,
		vector_dot(r->norm, r->dir) * 2));
	new_nearest = lenray(sc, &newray);
	color = 0;
	if (ret < 10 && new_nearest > EPS && newray.obj)
	{
		if (newray.obj && (newray.obj->type))
			color = diffuse(sc, &newray, newray.obj, new_nearest, newray.obj->c_o);
		color_composants(color, tmp_rgb);
		color_composants(col, rgb);
		rgb[0] = rgb[0] * (1 - (eff / 100)) + tmp_rgb[0] * (eff / 100);
		rgb[1] = rgb[1] * (1 - (eff / 100)) + tmp_rgb[1] * (eff / 100);
		rgb[2] = rgb[2] * (1 - (eff / 100)) + tmp_rgb[2] * (eff / 100);
		col = colorfromrgb(rgb);
		if (newray.obj->eff[1])
			col = reflexion(sc, &newray, new_nearest, col, ret + 1,
				(newray.obj->eff[1] > eff) ? eff : newray.obj->eff[1]);
	}
	else if (new_nearest < 0 && eff == 100)
		col = 0;
	return (col);
}

double	getnearesthit(t_ray *r, t_gen *raytracer, double x1, double y1, t_id *g)
{
	int		color;
	double	new_nearest;
	
	(void)g;
	r->dir = vector_normalize(new_vector(x1 - W_X / 2.0, W_Y / 2.0 - y1,
		(W_Y / 2.0) / tan(70*0.5)));
	new_nearest = lenray(raytracer->sc, r);
	color = 0;
	if (new_nearest >= 0)
	{
		if (r->obj && (r->obj->type))
		{
			color = diffuse(raytracer->sc, r, r->obj, new_nearest, color);
			if (r->obj->eff[1])
				color = reflexion(raytracer->sc, r, new_nearest, color, 0, r->obj->eff[1]);
		}
		gtk_put_pixel(raytracer->pixbuf, x1, y1, color);
	}
	return (new_nearest);	
}

void *display(void *z)
{
	t_obj		*tmp;
	t_id		*t;
	t_thread	*mt;
	t_ray r;
	int x;
	int y;

	mt = (t_thread*)z;
	r.start = new_vector(mt->s->sc->cam[0], mt->s->sc->cam[1], mt->s->sc->cam[2]);
	tmp = mt->s->sc->obj;
	t = mt->t;
	y = mt->lim[1] - 1;
	// pthread_mutex_lock(&(mt->s->lock_draw));
	while (++y < mt->lim[3])
	{
		x = mt->lim[0] - 1;
		while (++x < mt->lim[2])
			getnearesthit(&r, mt->s, x, y, t);
	}
	// pthread_mutex_unlock(&(mt->s->lock_draw));
	return (NULL);
}

void raytracing(t_gen *s)
{
	static t_id		t;
	static char		c = 0;
	int				j;
	pthread_t		p[MT];

	if (!c)
	{
		s->lock_draw = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		t.data = malloc(W_X * 3 * 1050);
		s->pixbuf = NULL;
		(!(t.z = ft_memalloc(sizeof(t_thread) * MT))) ? error(2, "Malloc") : 1;
		init_threads(t.z, &t, s);
		c = 1;
	}
	else
		ft_bzero(t.data, W_X * W_Y * 3);	
	if (!(s->pixbuf = gtk_new_image((unsigned char *)(t.data), W_X, W_Y)))
		error(4, "Unable to initialize pixbuf for GtkImage :'(\n");
	j = -1;
	while (++j < MT)
		pthread_create(&p[j], NULL, display, &t.z[j]);	// creation des threads	
	j = -1;
	while (++j < MT)
		pthread_join(p[j], NULL);	// synchro des threads
	gtk_put_image_to_window(GTK_IMAGE(s->pdrawarea), s->pixbuf);
	g_object_unref(s->pixbuf);
	gtk_widget_show_all(s->pwindow);
	gtk_main();
}
