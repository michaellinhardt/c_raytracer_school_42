/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:39:16 by vbauguen          #+#    #+#             */
/*   Updated: 2016/07/28 02:50:33 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

double noise(t_vector hitpoint)
{
	double noiseCoef;

	noiseCoef = 0;
	for (int level = 1; level < 100; level ++)
    {
        noiseCoef += (1.0 / level )  
        // différents coefficients en x, y  et z du Bruit de Perlinpinpin
            * fabs((perlin(fabs(level * 0.05 * hitpoint.x), fabs(level * 0.00 * hitpoint.y), fabs(level * 0.05 * hitpoint.z))));
    };
    if (noiseCoef > 1.0)
    	noiseCoef = 1;
    return (noiseCoef);
}


void sqrtc(double *color)
{
	color[0] = sqrtf(color[0]);
	color[1] = sqrtf(color[1]);
	color[2] = sqrtf(color[2]);
	// racine carree d'une couleur
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
	hitpoint = getHitpoint(r->start, r->dir, nearest);
	nb_spot = 0;
	while (spot)
	{
		spot =spot->next;
		++nb_spot;
	}
	spot = sc->spot;
	if (tmp->type != COMPLEXE)
		color_composants(tmp->c_o, rgb);
	else
		color_composants(col, rgb);
	is_ob = cast_shadow(sc->obj, hitpoint, spot, tmp);
	// is_ob = 1;
	ft_bzero(total_rgb, sizeof(double) * 3);
	if (is_ob)
	while (spot)
	{
		spot_pos = newVector(spot->spot[0], spot->spot[1], spot->spot[2]);
		light_dist = vectorDir(spot_pos, hitpoint);
		factor = vectorDot(light_dist, r->norm);
		color_composants(spot->c_s, tmp_rgb);
		if (factor < 0)
			factor = 0;
		if (factor > 0)
			colorNormalize(total_rgb, tmp_rgb, factor, 1);			
		spot = spot->next;
	}
	total_rgb[0] /= nb_spot;
	total_rgb[1] /= nb_spot;
	total_rgb[2] /= nb_spot;
	sqrtc(total_rgb);
	colorNormalize(rgb, total_rgb, is_ob /** noise(hitpoint)*/, 0);			
	return (colorfromrgb(rgb));
}

int 	reflexion(t_scene *sc, t_ray *r, double m, int col)
{
	t_vector newstartpoint;
	// double coeffreflection;
	t_ray newray;
	int color;


	color = 0;
	double new_nearest;

	newstartpoint = r->start;
	newray.start = getHitpoint(newstartpoint, r->dir, m);
	newray.dir = vectorDir(r->dir, vectorMultByScalar(r->norm, vectorDot(r->dir, r->norm) * 2));
	new_nearest = lenray(sc, &newray);

	if (new_nearest > 1)
	{
		if (newray.obj->type == SPHERE || newray.obj->type == PLAN || newray.obj->type == CYLINDRE || newray.obj->type == RECTANGLE || newray.obj->type == COMPLEXE)
			col = diffuse(sc, &newray, newray.obj, new_nearest, color);

	}
	else 
	{
		// color *= coeffreflection;
	}

	return col;

}

double	getnearesthit(t_ray *r, t_scene *sc, double x1, double y1, t_id *g)
{
	t_obj *s;
	int color;
	double new_nearest;

	s = sc->obj; // recuperation de la liste d'objets
	r->dir = newVector(x1 - W_X / 2.0, W_Y / 2.0 - y1, (W_Y / 2.0) / tan(70*0.5));	//initialisation des donnees de la camera 
	r->dir = vectorNormalize(r->dir);	// normalisation de la direction

	new_nearest = lenray(sc, r);
		color = 0;
	if (new_nearest >= 0)
	{
		if (r->obj && (r->obj->type == SPHERE|| r->obj->type == COMPLEXE || r->obj->type == PLAN || r->obj->type == CYLINDRE || r->obj->type == RECTANGLE))
		{
			color = diffuse(sc, r, r->obj, new_nearest, color);
			if (r->obj->eff[1])
				color = reflexion(sc, r, new_nearest, color);
		}
		mlx_image_put_pixel(g, x1, y1, color);
		/*
		** 		Si a la fin du calcul total on a bien trouve une intersection 
		** 		existante (nearest > 0), on lance la fonction qui permet de calculer  
		** 		le pourcentage de coloration de la couleur diffuse au point touche
		*/
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
	r.start = newVector(mt->s->sc->cam[0], mt->s->sc->cam[1], mt->s->sc->cam[2]); // Recuperation de la postion de la camera pour le multithread
	r.dir = newVector(mt->s->sc->cam[3], mt->s->sc->cam[4], mt->s->sc->cam[5]);	// Recuperation de la direction de la camera pour le multithread
	tmp = mt->s->sc->obj;
	t = mt->t;
	y = mt->lim[1] - 1;
	while (++y < mt->lim[3])
	{
		x = mt->lim[0] - 1;
		while (++x < mt->lim[2])
		{
			// Pour chaque pixel traite par le thread actuel, 
			getnearesthit(&r, mt->s->sc, x, y, t);
		}
	}
	return (NULL);
}


void raytracing(t_gen *s)
{
	static t_id t;
	static char c = 0;
	int j;
	pthread_t	p[MT];



	// initialisation minilibx
	if (!c)
	{
		t.mlx = mlx_init();
		t.win = mlx_new_window(t.mlx, W_X, W_Y, WIN_NAME);
		t.img = mlx_new_image(t.mlx, W_X, W_Y);
		t.data = mlx_get_data_addr(t.img, &t.bit_per_pixel, &t.s_line,
			&t.endian);
		t.bpp = t.bit_per_pixel / 8;
		(!(t.z = ft_memalloc(sizeof(t_thread) * MT))) ? error(2, "Malloc") : 1;
		init_threads(t.z, &t, s);
		c = 1;
	}
	else
	{
		mlx_clear_window(t.mlx, t.win);
		ft_bzero(t.data, W_Y * t.s_line);
	}
	j = -1;
	while (++j < MT)
		pthread_create(&p[j], NULL, display, &t.z[j]);	// creation des threads
	j = -1;
	while (++j < MT)
		pthread_join(p[j], NULL);	// synchro des threads
	// display(s->sc, r, &t);



	mlx_put_image_to_window(t.mlx, t.win, t.img, 0, 0);
	mlx_mouse_hook(t.win, mouse_functions, s);
	mlx_hook(t.win, 2, (1l << 0), press_key, s);				// hooks et autres trucs de la minilibx
	// mlx_hook(t.win, 3, (1L << 1), release_key, s);
	mlx_hook(t.win, 17, (1L << 17), quit_w, s);
	mlx_key_hook(t.win, key_reaction, &t);
	if (s->rep & SAVE)
	{
		print_bmp(t.data, t, s);
		s->rep ^= SAVE;
	}
	mlx_loop(t.mlx);
}