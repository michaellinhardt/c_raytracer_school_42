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
            * fabs((perlin(fabs(level * 0.05 * hitpoint.x), fabs(level * 0.05 * hitpoint.y), fabs(level * 0.05 * hitpoint.z))));
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

int diffuse(t_scene *sc, t_ray *r, t_obj *tmp, double nearest)
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
	color_composants(tmp->c_o, rgb);
	is_ob = cast_shadow(sc->obj, hitpoint, spot, tmp);
	ft_bzero(total_rgb, sizeof(double) * 3);
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


double	getnearesthit(t_ray *r, t_scene *sc, double x1, double y1, t_id *g)
{
	double nearest[2];
	double t;
	t_obj *tmp;
	t_obj *s;
	t_vector norm;
	int color;

	color = 0;
	s = sc->obj; // recuperation de la liste d'objets
	tmp = NULL;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	t = 0;
	double tmp_near[2];

	while (s)
	{
		if (!s->eff[3])
		{
			s = s->next;
			continue ;
		}
		tmp_near[0] = -1;
		tmp_near[1] = INT_MAX;
		r->dir = newVector(x1 - W_X / 2.0, W_Y / 2.0 - y1, (W_Y / 2.0) / tan(70*0.5));	//initialisation des donnees de la camera 
		r->dir = vectorNormalize(r->dir);	// normalisation de la direction
		if (s->type == SPHERE)
			t = intersectRaySphere(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == PLAN)
			t = intersectRayPlane(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == CYLINDRE)
			t = intersectRayCylindre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == RECTANGLE)
			t = intersectRayCarre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == COMPLEXE)
			t = intersectRayComplex(r, s, &tmp_near[0], &tmp_near[1]);
		if (t > 0 && tmp_near[0] != -1)
		{
			if (nearest[0] == -1 || (tmp_near[0] < nearest[0]) || tmp_near[1] > nearest[1])
			{
				if (nearest[0] == -1 || tmp_near[0] < nearest[0])
					nearest[0] = tmp_near[0];
				if (nearest[1] == INT_MAX || tmp_near[1] > nearest[1])
					nearest[1] = tmp_near[1];
				norm = r->norm;
			}
			t = 0;
		}
		s = s->next;
	}
	t = 0;
	double new_nearest = -1;
	s = sc->obj; // recuperation de la liste d'objets
	while (s) //pour toute la liste d'objets
	{
		if (s->eff[3])
		{
			s = s->next;
			continue ;
		}
		r->dir = newVector(x1 - W_X / 2.0, W_Y / 2.0 - y1, (W_Y / 2.0) / tan(70*0.5));	//initialisation des donnees de la camera 
		r->dir = vectorNormalize(r->dir);	// normalisation de la direction
		if (s->type == SPHERE)
			t = intersectRaySphere(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == PLAN)
			t = intersectRayPlane(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == CYLINDRE)
			t = intersectRayCylindre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == RECTANGLE)
			t = intersectRayCarre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == COMPLEXE)
			t = intersectRayComplex(r, s, &tmp_near[0], &tmp_near[1]);
		if ((t < new_nearest && t > 0)|| (new_nearest < 0 && t > 0))
		{
			// si la distance actuelle calculee est plus petite que la precedente, on garde en memoire 
			//: la nouvelle plus courte intersection, l'objet concerne, et la normale du point touche
			if (t > nearest[0] && t < nearest[1] && t > 0 && nearest[0] > 0 /*&& nearest[1] < INT_MAX*/)
			{
				if (tmp_near[1] < nearest[1])
				{
					s = s->next;
					continue;
				}
				new_nearest = nearest[1];
				tmp = s;
				norm.x = -norm.x;
				norm.y = -norm.y;
				norm.z = -norm.z;
			}
			else
			{
				new_nearest = t;
				tmp = s;
				norm = r->norm;
			}
		}
		s = s->next; //objet suivant
	}
	if (new_nearest >= 0)
	{
		r->norm = norm;
		color = 0;
		if (tmp && (tmp->type == SPHERE|| tmp->type == COMPLEXE || tmp->type == PLAN || tmp->type == CYLINDRE || tmp->type == RECTANGLE))
			color = diffuse(sc, r, tmp, new_nearest);
		// if (tmp)
		mlx_image_put_pixel(g, x1, y1, color);
		/*
		** 		Si a la fin du calcul total on a bien trouve une intersection 
		** 		existante (nearest > 0), on lance la fonction qui permet de calculer  
		** 		le pourcentage de coloration de la couleur diffuse au point touche
		*/
	}
	return (nearest[0]);	
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