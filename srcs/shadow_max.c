/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 20:10:10 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/27 18:33:43 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

double cast_shadow(t_obj *s, t_vector hitpoint, t_spot *spot, t_obj *tmp)
{
	double is_ob;
	double t;
	t_ray	r;
	t_obj	*object;
	int 	i;
	t_vector spot_pos;
	double truc[2];
	double nearest[2];
	int col = 0;

	(void)tmp;
	is_ob = 0;
	i = 0;
	object = s;
	r.start = newVector(hitpoint.x, hitpoint.y, hitpoint.z);
	while (spot)
	{
		s = object;
		spot_pos = newVector(spot->spot[0], spot->spot[1], spot->spot[2]);
		r.dir = vectorDir(spot_pos, r.start);
		nearest[0] = -1;
		nearest[1] = INT_MAX;
		while (s)
		{
			if (!s->eff[3])
			{
				s = s->next;
				continue ;
			}
			if (s->type == SPHERE)
				t = intersectRaySphere(&r, s, &nearest[0], &nearest[1]); // a chaque forme sa formule mathematique 
			else if (s->type == PLAN)
				t = intersectRayPlane(&r, s, &nearest[0], &nearest[1]); // a chaque forme sa formule mathematique 
			else if (s->type == CYLINDRE)
				t = intersectRayCylindre(&r, s, &nearest[0], &nearest[1]); // a chaque forme sa formule mathematique 
			else if (s->type == RECTANGLE)
				t = intersectRayCarre(&r, s, &nearest[0], &nearest[1]); // a chaque forme sa formule mathematique 
			else if (s->type == COMPLEXE)
				t = intersectRayComplex(&r, s, &nearest[0], &nearest[1], &col);
			if (nearest[0] != -1)
			{
				// norm = r->norm;
				// t = 0;
			}
			s = s->next;
		}
		s = object;
		while (s)
		{
			if (s->eff[3])
			{
				s = s->next;
				continue ;
			}
			t = 0;
			if (s->type == SPHERE)
				t = intersectRaySphere(&r, s, &truc[0], &truc[1]);
			else if (s->type == PLAN)
				;
			else if (s->type == CYLINDRE)
				t = intersectRayCylindre(&r, s, &truc[0], &truc[1]);
			else if (s->type == RECTANGLE)
				t = intersectRayCarre(&r, s, &truc[0], &truc[1]);
			else if (s->type == COMPLEXE)
				t = intersectRayComplex(&r, s, &truc[0], &truc[1], &col);
				if (t > nearest[0] && t < nearest[1] && t > 0.001 && nearest[0] > 0 /*&& nearest[1] < INT_MAX*/)
				{
					if (truc[1] > nearest[1])
					{
						s = s->next;
						is_ob += 1;
						break ;
					}
				}
				else if (t > 0.001)
				{

					is_ob += 1;
					break ;
				}

			// if (t > 0.001 && t < nearest[1] && t > nearest[0])
			// {
				// is_ob += 1;
				// break ;
			// }
			s = s->next;
		}
		spot = spot->next;
		++i;
	}
	return ((is_ob > 0) ? (double)(i - is_ob) / i : 1);
}
	