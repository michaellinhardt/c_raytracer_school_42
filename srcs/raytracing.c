/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2016/12/18 06:54:07 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"
#include <gui.h>
#include <stdio.h>

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
	tmp = new_vector(newray.dir.x * EPS, newray.dir.y * EPS, newray.dir.z * EPS);
	newray.start = vector_add(newray.start, tmp);
	new_nearest = lenray(sc, &newray);
	if (new_nearest > EPS)
	{

		coeffreflex = newray.obj->eff[1] / 100;
		// coeffreflex = r->obj->eff[1] / 100;

		// coefftransp = newray.obj->eff[0] / 100;
		coefftransp = r->obj->eff[0] / 100;

		coeffnone = 1 - coefftransp - coeffreflex;

		// if (coeffnone < 0)
		// {
		// 	coeffnone = 0;
		// 	coefftransp = coefftransp / (coeffreflex + coefftransp);
		// 	coeffreflex = coeffreflex / (coeffreflex + coefftransp);

		// }


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
		
		// if (!coeffreflex)
		// {
			rgb[0] = rgb[0] * coeffnone + tmp_rgb[0] * coefftransp + refl_rgb[0] * coeffreflex;
			rgb[1] = rgb[1] * coeffnone + tmp_rgb[1] * coefftransp + refl_rgb[1] * coeffreflex;
			rgb[2] = rgb[2] * coeffnone + tmp_rgb[2] * coefftransp + refl_rgb[2] * coeffreflex;
		// }
		// else
		// {
			// rgb[0] = rgb[0] * coeffnone + /*tmp_rgb[0] * coefftransp +*/ refl_rgb[0] * coeffreflex * 1.35;
			// rgb[1] = rgb[1] * coeffnone + /*tmp_rgb[1] * coefftransp +*/ refl_rgb[1] * coeffreflex * 1.35;
			// rgb[2] = rgb[2] * coeffnone + /*tmp_rgb[2] * coefftransp +*/ refl_rgb[2] * coeffreflex * 1.35;
		// }

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

double noise(t_ray *r, t_vector hitpoint)
{
	double noiseCoef;
	int level;


	// (void)r;
	noiseCoef = 0;
	level = 1;
	while (level < 50)
    {
        noiseCoef += (1.0 / level)  
            * fabs((perlin(	fabs(level * 0.05 * hitpoint.x),
            				fabs(level * 0.05 * hitpoint.y),
            				fabs(level * 0.05 * hitpoint.z))));
    	level++;
    }
    if (noiseCoef > 1.0)
    	noiseCoef = 1;


	float noiseCoefx = perlin(hitpoint.x, hitpoint.y, hitpoint.z);
 	float noiseCoefy = perlin(hitpoint.y, hitpoint.z, hitpoint.x);
 	float noiseCoefz = perlin(hitpoint.z, hitpoint.x, hitpoint.y);
    // r->norm.x = noiseCoefx;
    // r->norm.y = noiseCoefy;
    // r->norm.z = noiseCoefz;







	r->norm.x = (1.0f - 0.1 ) * r->norm.x + 0.1 * noiseCoefx;
 	r->norm.y = (1.0f - 0.1 ) * r->norm.y + 0.1 * noiseCoefy;
 	r->norm.z = (1.0f - 0.1 ) * r->norm.z + 0.1 * noiseCoefz; 





 	if (r->obj->eff[0])
    	r->norm = vectormultby_scalar(r->norm, -1);

    r->norm = vector_normalize(r->norm);

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

typedef struct    s_color
{
	t_spot      *spot;
	t_vector    hitpoint;
	t_vector    mirror_vec_light;
	t_vector    vec_obj_eye;
	t_vector    vec_obj_light;
	t_vector    spot_pos;
	double      dot_light_norm;
	double      intensity[3];
	double      i_a[3];
	double      i_l[3];
	double      rgb[3];
	double      col;
	int       i;
}         t_color;

static int		ft_shadow(t_obj *s, t_color *c)
{
	t_ray	r;
	double	dist[2];
	t_inter	i;

	r.start = new_vector(c->spot_pos.x, c->spot_pos.y, c->spot_pos.z);
	dist[0] = vector_dist(r.start, c->hitpoint);
	r.dir = vector_normalize(vector_sub(c->hitpoint, c->spot_pos));
	while (s)
	{
		dist[1] = lenray_type(&r, s, &i, 0);
		if (dist[1] > EPS && dist[1] < dist[0] - EPS)
			return (1);
		s = s->next;
	}
	return (0);
}

static double	diffuse_shadow_specular(t_ray *r, t_color *c, t_scene *sc,
t_obj *tmp)
{
	double speculaire;
	double obj_dotn;
	(void)sc;
	speculaire = 1;
	c->spot_pos = new_vector(c->spot->pos[0], c->spot->pos[1],
	c->spot->pos[2]);
	color_composants(c->spot->c_s, c->i_l);
	c->vec_obj_light = vector_normalize(vector_sub(c->spot_pos, c->hitpoint));
	c->dot_light_norm = vector_dot(c->vec_obj_light, r->norm);
	c->i_l[c->i] = (ft_shadow(sc->obj, c) == 0) ? c->i_l[c->i] : 0;
	if (vector_dot(r->norm, vector_normalize(vector_sub(c->hitpoint,
	c->spot_pos))) > 0 && tmp->type == PLAN)
		return (0);
	// if (c->i_l[c->i] != 0)
	// 	printf("la\n");
	c->dot_light_norm = (c->dot_light_norm > 0 && c->dot_light_norm <= 90)
	? c->dot_light_norm : 0;
	c->mirror_vec_light = vector_normalize(vector_sub(vectormultby_scalar(
	r->norm, 2 * vector_dot(r->norm, c->vec_obj_light)), c->vec_obj_light));
	obj_dotn = vector_dot(r->norm, c->vec_obj_light);
	c->i_l[c->i] = (obj_dotn > 0 && obj_dotn <= 90) ? c->i_l[c->i] : 0;
	speculaire = vector_dot(c->mirror_vec_light, c->vec_obj_eye);
	speculaire = (speculaire > 0 && speculaire <= 90) ? speculaire : 0;
	return (c->i_l[c->i] = 0 ? 0 : c->i_l[c->i] * (c->rgb[c->i] *
	c->dot_light_norm + 1 * pow(speculaire, 66)));
}

int diffuse(t_scene *sc, t_ray *r, t_obj *tmp, double nearest, int col)
{
t_color  c;

(void)col;
if (!(tmp->text))
	color_composants(tmp->c_o, c.rgb);
else
	color_composants(texture(tmp, get_hitpoint(r->start, r->dir, nearest)), c.rgb);
color_composants(sc->amb[0], c.i_a);
c.hitpoint = get_hitpoint(r->start, r->dir, nearest);
c.vec_obj_eye = vector_normalize(vector_sub(r->start, c.hitpoint));
if (tmp->type == PLAN && vector_dot(c.vec_obj_eye, r->norm) < 0)
  r->norm = vectormultby_scalar(r->norm, -1);
c.i = 0;
while (c.i < 3)
{
  c.spot = sc->spot;
  c.col = 0;
  while (c.spot)
  {
    c.col = c.col + diffuse_shadow_specular(r, &c, sc, tmp);
    c.spot = c.spot->next;

  }
  c.intensity[c.i] = sc->amb[1] * c.rgb[c.i] * c.i_a[c.i] + c.col;
  c.i++;
}
// color_normalize(c.intensity, c.intensity, noise(r, c.hitpoint), 0);
return (colorfromrgb(c.intensity));
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
	if (ret < 15 && new_nearest > EPS && newray.obj)
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
		// if (coefftransp)
		// {
		// 	color_composants(col, tmp_rgb);
		// 	coeffreflex = 0;
		// }
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
	// double ebloui;
	// t_vector poscam;
	// t_vector dirlight;

	r->dir = vector_normalize(new_vector(x1 - W_X / 2.0, W_Y / 2.0 - y1,
		(W_Y / 2.0) / tan(70 * 0.5)));
	new_nearest = lenray(raytracer->sc, r);
	color = 0;
	col = 0;
	diffusecolor = 0;
	// poscam = new_vector(r->start.x, r->start.y, r->start.z);
	// dirlight = vector_sub(, );
	if (new_nearest >= EPS)
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
	// antialiasing((unsigned char *)s->data, gdk_pixbuf_get_rowstride(s->pixbuf), -3);
	pixbuffer = gdk_pixbuf_get_pixels(s->pixbuf);
	merge_chuncks(pixbuffer, s->data);	
	gtk_put_image_to_window(GTK_IMAGE(s->pdrawarea), s->pixbuf);
	free(pixbuffer);
	g_object_unref(s->pixbuf);
}
