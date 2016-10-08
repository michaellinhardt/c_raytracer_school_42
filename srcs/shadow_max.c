/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 20:10:10 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/24 17:28:52 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void	is_shadow(t_obj *s, double *nearest, t_ray r, double *is_ob)
{
	double	t[3];
	int		col;

	col = 0;
	t[0] = 1;
	while (s)
	{
		if (!s->eff[3] && !(s->type & PLAN))
		{
			t[2] = lenray_type(&r, s, t, &col);
			if (t[2] > nearest[0] && t[2] < nearest[1]
				&& t[2] > EPS && nearest[0] > EPS)
			{
				if (t[1] > nearest[1])
				{
					s = s->next;
					*is_ob += (1 - s->eff[0] / 100);
					return ;
				}
			}
			else if (t[2] > EPS && (*is_ob += (1 - s->eff[0] / 100)))
				return ;
		}
		s = s->next;
	}
}

double		cast_shadow(t_obj *s, t_vector hitpoint, t_spot *spot, t_obj *obj)
{
	t_ray		r;
	double			i[3];
	t_vector	spot_pos;
	double		nearest[2];

	i[2] = 0;
	i[0] = 0;
	r.start = new_vector(hitpoint.x, hitpoint.y, hitpoint.z);
	while (spot && ++i[0])
	{
		s = obj;
		if (spot->type & POINT)
		{
			spot_pos = new_vector(spot->pos[0], spot->pos[1], spot->pos[2]);
			r.dir = vector_dir(spot_pos, r.start);
		}
		else if (spot->type & DIR)
			r.dir = vector_normalize(new_vector(spot->pos[3], spot->pos[4], spot->pos[5]));
		nearest[0] = -1;
		nearest[1] = INT_MAX;
		while (s)
		{
			if (s->eff[3])
				lenray_type(&r, s, nearest, (int*)&i[1]);
			s = s->next;
		}
		is_shadow(obj, nearest, r, &i[2]);
		spot = spot->next;
	}
	return ((i[2] > 0) ? (double)(i[0] - i[2]) / i[0] : 1);
}
