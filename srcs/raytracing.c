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

int refraction(t_scene *sc, t_ray *r, double dist, int col, int ret, double refrini)
{
	t_ray newray;
	double refrhit;
	double ndoti;
	double two_ndoti;
	double ndoti2;
	double new_nearest;
	t_vector tmp;
	(void)ret;
	int color;
	int reflcolor;
	double 	refl_rgb[3];
	double	tmp_rgb[3];
	double	rgb[3];
	double a, b, b2, d2;


	double coefftransp = 0;
	double coeffreflex = 0;
	double coeffnone = 0;



	color = 0;
	reflcolor = 0;
	refrhit = r->obj->eff[2];
	newray.start = get_hitpoint(r->start, r->dir, dist);
	r->dir = vectormultby_scalar(r->dir, -1);
	ndoti = vector_dot(r->dir, r->norm);
	ndoti2 = ndoti * ndoti;
	if (ndoti > 0)
	{
		b = refrini / refrhit;
		b2 = b * b;
	}
	else 
	{
		b = refrhit / refrini;
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
	tmp = new_vector(newray.dir.x * 0.001, newray.dir.y * 0.001, newray.dir.z * 0.001);
	newray.start = vector_add(newray.start, tmp);
	new_nearest = lenray(sc, &newray);
	if (new_nearest > 0.001)
	{

		coeffreflex = newray.obj->eff[1] / 100;
		// coeffreflex = r->obj->eff[1] / 100;

		// coefftransp = newray.obj->eff[0] / 100;
		coefftransp = r->obj->eff[0] / 100;

		coeffnone = 1 - coefftransp - coeffreflex;

		if (coeffnone < 0)
		{
			coeffnone = 0;
			coefftransp = coefftransp / (coeffreflex + coefftransp);
			coeffreflex = coeffreflex / (coeffreflex + coefftransp);

		}


		if (newray.obj && (newray.obj->type == SPHERE || newray.obj->type == PLAN || newray.obj->type == CYLINDRE || newray.obj->type == RECTANGLE || newray.obj->type == COMPLEXE))
			color = diffuse(sc, &newray, newray.obj, new_nearest, newray.obj->c_o);
		if (newray.obj->eff[1])
			reflcolor = reflexion(sc, &newray, new_nearest, col, 0,	newray.obj->eff[1]);

		color_composants(color, tmp_rgb);
		color_composants(col, rgb);
		color_composants(reflcolor, refl_rgb);

		rgb[0] = rgb[0] * (1 - coefftransp) + tmp_rgb[0] * (coefftransp);
		rgb[1] = rgb[1] * (1 - coefftransp) + tmp_rgb[1] * (coefftransp);
		rgb[2] = rgb[2] * (1 - coefftransp) + tmp_rgb[2] * (coefftransp);
		
		if (!coeffreflex)
		{
			rgb[0] = rgb[0] * coeffnone + tmp_rgb[0] * coefftransp;// + refl_rgb[0] * coeffreflex;
			rgb[1] = rgb[1] * coeffnone + tmp_rgb[1] * coefftransp;// + refl_rgb[1] * coeffreflex;
			rgb[2] = rgb[2] * coeffnone + tmp_rgb[2] * coefftransp;// + refl_rgb[2] * coeffreflex;
		}
		else
		{
			rgb[0] = rgb[0] * coeffnone + /*tmp_rgb[0] * coefftransp +*/ refl_rgb[0] * coeffreflex * 1.35;
			rgb[1] = rgb[1] * coeffnone + /*tmp_rgb[1] * coefftransp +*/ refl_rgb[1] * coeffreflex * 1.35;
			rgb[2] = rgb[2] * coeffnone + /*tmp_rgb[2] * coefftransp +*/ refl_rgb[2] * coeffreflex * 1.35;
		}

		color = colorfromrgb(rgb);
		newray.norm = vectormultby_scalar(r->norm, -1);

		if (r->obj->name != newray.obj->name)
		{
			// newray.norm = r->norm;
			// newray.norm = vectormultby_scalar(newray.norm, -1);
			refrhit = 1;
		}

		if (newray.obj->eff[2] && newray.obj->eff[0])
			color = refraction(sc, &newray, new_nearest, color, ret + 1, refrhit);
	}
	return (color);
}

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
	// color_normalize(rgb, total_rgb, is_ob * noise(hitpoint), 0);
	return (colorfromrgb(rgb));
}

int 	reflexion(t_scene *sc, t_ray *r, double m, int col, int ret, double eff)
{
	t_ray	newray;
	int		color;
	int 	refrcolor;
	double 	refr_rgb[3];
	double	tmp_rgb[3];
	double	rgb[3];
	double 	new_nearest;
	double coeffnone = 0;
	double coeffreflex = 0;
	double coefftransp = 0;

	newray.start = get_hitpoint(r->start, r->dir, m);
	newray.dir = vector_dir(r->dir, vectormultby_scalar(r->norm,
		vector_dot(r->norm, r->dir) * 2));
	new_nearest = lenray(sc, &newray);
	color = 0;
	refrcolor = 0;
	if (ret < 25 && new_nearest > EPS && newray.obj)
	{
		if (newray.obj && (newray.obj->type))
			color = diffuse(sc, &newray, newray.obj, new_nearest, newray.obj->c_o);
		if (newray.obj->eff[0] && newray.obj->eff[2])
			refrcolor = refraction(sc, &newray, new_nearest, 0, color, 1);
		
		color_composants(color, tmp_rgb);
		color_composants(col, rgb);
		color_composants(refrcolor, refr_rgb);

		// coeffreflex = newray.obj->eff[1] / 100;
		coeffreflex = eff / 100;
		coefftransp = newray.obj->eff[0] / 100;
		if (coefftransp)
		{
			color_composants(col, tmp_rgb);
			coeffreflex = 0;
		}
		coeffnone = 1 - coefftransp - coeffreflex;
		if (coeffnone < 0)
		{
			coeffnone = 0;
			coefftransp = coefftransp / (coeffreflex + coefftransp);
			coeffreflex = coeffreflex / (coeffreflex + coefftransp);
		}
		rgb[0] = rgb[0] * (1 - coeffreflex) + tmp_rgb[0] * coeffreflex;
		rgb[1] = rgb[1] * (1 - coeffreflex) + tmp_rgb[1] * coeffreflex;
		rgb[2] = rgb[2] * (1 - coeffreflex) + tmp_rgb[2] * coeffreflex;
		rgb[0] = (coeffnone) * rgb[0] + (coeffreflex) * tmp_rgb[0] + (coefftransp) * refr_rgb[0];
		rgb[1] = (coeffnone) * rgb[1] + (coeffreflex) * tmp_rgb[1] + (coefftransp) * refr_rgb[1];
		rgb[2] = (coeffnone) * rgb[2] + (coeffreflex) * tmp_rgb[2] + (coefftransp) * refr_rgb[2];

		// if (newray.obj->eff[0])
		// 	printf("coeffnone = %lf, coefftransp = %lf, coeffreflex = %lf\n", coeffnone, coefftransp, coeffreflex);

		col = colorfromrgb(rgb);
		if (newray.obj->eff[1])
			col = reflexion(sc, &newray, new_nearest, col, ret + 1,
				newray.obj->eff[1]);

	}
	else if (new_nearest <= 0)
	{
		color_composants(col, tmp_rgb);
		tmp_rgb[0] = tmp_rgb[0] * ( coeffreflex);
		tmp_rgb[1] = tmp_rgb[1] * ( coeffreflex);
		tmp_rgb[2] = tmp_rgb[2] * ( coeffreflex);
		col = colorfromrgb(tmp_rgb);
		// col = 0;
	}
	return (col);
}

double	getnearesthit(t_ray *r, t_gen *raytracer, double x1, double y1)
{
	double	coeffreflex = 0;
	double	coefftransp = 0;
	double	coeffnone = 0;
	double	reflexion3[3];
	double	new_nearest;
	double	diffuse3[3];
	double	refrac3[3];
	int		diffusecolor;
	int		color;
	int		col;

	r->dir = vector_normalize(new_vector(x1 - W_X / 2.0, W_Y / 2.0 - y1,
		(W_Y / 2.0) / tan(70 * 0.5)));
	new_nearest = lenray(raytracer->sc, r);
	color = 0;
	col = 0;
	diffusecolor = 0;
	if (new_nearest >= 0)
	{
		if (r->obj && (r->obj->type))
		{
			diffusecolor = diffuse(raytracer->sc, r, r->obj, new_nearest, r->obj->c_o);
			if (r->obj->eff[1])
				col = reflexion(raytracer->sc, r, new_nearest, diffusecolor, 0, r->obj->eff[1]);
			if (r->obj->eff[2] && r->obj->eff[0])
				color = refraction(raytracer->sc, r, new_nearest, 0, diffusecolor, 1);
		}
		coefftransp = r->obj->eff[0] / 100;
		coeffreflex = r->obj->eff[1] / 100;
		coeffnone = 1 - coeffreflex - coefftransp;
		color_composants(diffusecolor, diffuse3);
		color_composants(color, refrac3);
		color_composants(col, reflexion3);
		diffuse3[0] = coeffreflex * reflexion3[0] + coefftransp * refrac3[0] + coeffnone * diffuse3[0];
		diffuse3[1] = coeffreflex * reflexion3[1] + coefftransp * refrac3[1] + coeffnone * diffuse3[1];
		diffuse3[2] = coeffreflex * reflexion3[2] + coefftransp * refrac3[2] + coeffnone * diffuse3[2];
		color = colorfromrgb(diffuse3);

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
	antialiasing((unsigned char *)s->data, gdk_pixbuf_get_rowstride(s->pixbuf), -3);
	// abstract((unsigned char *)s->data, gdk_pixbuf_get_rowstride(s->pixbuf), -3);
	pixbuffer = gdk_pixbuf_get_pixels(s->pixbuf);
	merge_chuncks(pixbuffer, s->data);	
	gtk_put_image_to_window(GTK_IMAGE(s->pdrawarea), s->pixbuf);
	free(pixbuffer);
	g_object_unref(s->pixbuf);
}
