/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2016/08/24 17:25:54 by ocarta-l         ###   ########.fr       */
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

int texture_sphere(t_obj *tmp, t_vector hitpoint)
{
	t_vector	v_n;
	t_vector	v_e;
	t_vector	v_p;
	double		u;
	double		v;
	double		phi;
	double		theta;

	v_n = (new_vector(0, -1, 0));
	v_e = (new_vector(1, 0, 0));
	v_p = vector_normalize(vector_sub(hitpoint, new_vector(tmp->pos[0], tmp->pos[1], tmp->pos[2])));
	phi = acosf(-vector_dot(vector_normalize(v_n),vector_normalize(v_p)));
	v = phi / M_PI;
	theta = acosf(vector_dot(vector_normalize(v_p), vector_normalize(v_e)) / (sinf(phi))) / (8 * M_PI);
	u = (vector_dot(vector_cross(v_n, v_e), hitpoint) > 0) ? theta : 1 - theta;
	if (tmp->text & EARTH)
		return (texture_earth(u, v, NULL, NULL));
	else if (tmp->text & FIRE)
		return (texture_fire(u, v, NULL, NULL));
	else if (tmp->text & BLACK)
		return (texture_black(u, v, NULL, NULL));
	else if (tmp->text & ICE)
		return (texture_ice(u, v, NULL, NULL));
	return (0);
}

int texture(t_obj *tmp, t_vector hitpoint)
{
	if (tmp->type & SPHERE)
		return (texture_sphere(tmp, hitpoint));
	return (0);
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
	if (!(tmp->type & COMPLEXE))
	{
		if (!(tmp->text))
			color_composants(tmp->c_o, rgb);
		else
			color_composants(texture(tmp, hitpoint), rgb);
	}
	else
		color_composants(col, rgb);
	spot = sc->spot;
	is_ob = cast_shadow(sc->obj, hitpoint, spot, sc->obj);
	ft_bzero(total_rgb, sizeof(double) * 3);
	if (is_ob)
		while (spot)
		{
			if (spot->type & POINT)
			{
				spot_pos = new_vector(spot->pos[0], spot->pos[1], spot->pos[2]);
				light_dist = vector_dir(spot_pos, hitpoint);
			}
			else if (spot->type & DIR)
			{
				light_dist = vector_normalize(new_vector(spot->pos[3], spot->pos[4], spot->pos[5]));
			}
			factor = vector_dot(light_dist, r->norm);
			color_composants(spot->c_s, tmp_rgb);
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

double	getnearesthit(t_ray *r, t_gen *raytracer, double x1, double y1)
{
	int		color;
	double	new_nearest;
	
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
		gtk_put_pixel(raytracer->pixbuf, x1, y1, color, raytracer);
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
	while (++y < mt->lim[3])
	{
		x = mt->lim[0] - 1;
		while (++x < mt->lim[2])
			getnearesthit(&r, mt->s, x, y);
	}
	return (NULL);
}

static void		merge_chuncks(void	*dest, void const *src)
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

void raytracing(t_gen *s)
{
	static t_id		t;
	static char		c = 0;
	int				j;
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
	j = -1;
	while (++j < MT)
		pthread_create(&p[j], NULL, display, &t.z[j]);	// creation des threads	
	j = -1;
	while (++j < MT)
		pthread_join(p[j], NULL);	// synchro des threads
	j = -1;
	pixbuffer = gdk_pixbuf_get_pixels(s->pixbuf);
	merge_chuncks(pixbuffer, s->data);	
	gtk_put_image_to_window(GTK_IMAGE(s->pdrawarea), s->pixbuf);
	free(pixbuffer);
	g_object_unref(s->pixbuf);
}
