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
		while (s)
		{
			t = 0;
			if (s->type == SPHERE)
				t = intersectRaySphere(&r, s, 0, 0);
			else if (s->type == PLAN)
				;
			else if (s->type == CYLINDRE)
				t = intersectRayCylindre(&r, s, 0, 0);
			else if (s->type == RECTANGLE)
				t = intersectRayCarre(&r, s, 0, 0);
			if (t > 0.001)
			{
				is_ob += 1;
				break ;
			}
			s = s->next;
		}
		spot = spot->next;
		++i;
	}
	return ((is_ob > 0) ? (double)(i - is_ob) / i : 1);
}
	