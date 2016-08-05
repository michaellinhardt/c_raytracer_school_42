
#include "h_raystruct.h"

double lenray(t_scene *sc, t_ray *r)
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
	//	r->dir = newVector(x1 - W_X / 2.0, W_Y / 2.0 - y1, (W_Y / 2.0) / tan(70*0.5));	//initialisation des donnees de la camera 
	//	r->dir = vectorNormalize(r->dir);	// normalisation de la direction
		if (s->type == SPHERE)
			t = intersectRaySphere(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == PLAN)
			t = intersectRayPlane(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == CYLINDRE)
			t = intersectRayCylindre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == RECTANGLE)
			t = intersectRayCarre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == COMPLEXE)
			t = intersectRayComplex(r, s, &tmp_near[0], &tmp_near[1], &color);
		if (t > 1 && tmp_near[0] != -1)
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
		color = 0;
	while (s) //pour toute la liste d'objets
	{
		if (s->eff[3])
		{
			s = s->next;
			continue ;
		}
	//	r->dir = newVector(x1 - W_X / 2.0, W_Y / 2.0 - y1, (W_Y / 2.0) / tan(70*0.5));	//initialisation des donnees de la camera 
//		r->dir = vectorNormalize(r->dir);	// normalisation de la direction
		if (s->type == SPHERE)
			t = intersectRaySphere(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == PLAN)
			t = intersectRayPlane(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == CYLINDRE)
			t = intersectRayCylindre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == RECTANGLE)
			t = intersectRayCarre(r, s, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (s->type == COMPLEXE)
			t = intersectRayComplex(r, s, &tmp_near[0], &tmp_near[1], &color);
		if ((t < new_nearest && t > 1) || (new_nearest < 0 && t > 1))
		{
			// si la distance actuelle calculee est plus petite que la precedente, on garde en memoire 
			//: la nouvelle plus courte intersection, l'objet concerne, et la normale du point touche
			if (t > nearest[0] && t < nearest[1] && nearest[0] > 0 /*&& nearest[1] < INT_MAX*/)
			{
				if (tmp_near[1] <= nearest[1] && tmp_near[0] >= nearest[0])
				{
					s = s->next;
					continue;
				}
				// nearest[0] += 1;
				new_nearest = nearest[1];
				if (s->type != COMPLEXE)
					tmp = s;
				else
					tmp = r->obj;
				if (tmp->type == SPHERE)
				{
				norm.x = -r->norm.x;
				norm.y = -r->norm.y;
				norm.z = -r->norm.z;
				}
			}
			else
			{
				new_nearest = t;
				if (s->type != COMPLEXE)
					tmp = s;
				else
					tmp = r->obj;
				norm = r->norm;
			}
		}
		s = s->next; //objet suivant
	}
	if (new_nearest > 0)
	{
		r->norm = norm;
		r->obj = tmp;
	}
	return (new_nearest);
}