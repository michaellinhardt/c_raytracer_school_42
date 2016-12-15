#include "raystruct.h"

double intersectray_complex(t_ray *r, t_obj *p, int *col)
{
	double		t;
	t_obj		*tmp;
	t_obj		*temp;
	double		nearest[2];
	t_inter		i;
	t_vector	norm;
	double		new_nearest;

	tmp = p->comp;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	while (tmp)
	{
		if (tmp->eff[3])
		{
			i.inter1 = -1;
			i.inter2 = INT_MAX;
			t = lenray_type(r, tmp, &i, col);
			if (t > EPS && i.inter1 != -1)
				if (nearest[0] == -1 || (i.inter1 < nearest[0]) || i.inter2 > nearest[1])
				{
					if (nearest[0] == -1 || i.inter1 < nearest[0])
						nearest[0] = i.inter1;
					if (nearest[1] == INT_MAX || i.inter2 > nearest[1])
						nearest[1] = i.inter2;
					norm = r->norm;
				}
		}
		tmp = tmp->next;
	}
	tmp = p->comp;
	temp = NULL;
	new_nearest = -1;
	while (tmp) //pour toute la liste d'objets
	{
		if (!tmp->eff[3])
		{
			t = lenray_type(r, tmp, &i, col);
			if ((t < new_nearest && t > EPS)|| (new_nearest < 0 && t > EPS))
			{
				if (t > nearest[0] && t < nearest[1] && nearest[0] > 0)
				{
					if (i.inter2 <= nearest[1] && i.inter1 >= nearest[0])
					{
						tmp = tmp->next;
						continue;
					}
					new_nearest = nearest[1];
					temp = tmp;
					r->obj = tmp;
					norm = vector_rev(norm);
				}
				else
				{
					new_nearest = t;
					temp = tmp;
					r->obj = tmp;
					norm = r->norm;
				}
			}
		}
		tmp = tmp->next;
	}
	if (new_nearest > EPS)
	{
		*col = temp->c_o;
		r->norm = norm;
	}
	return ((new_nearest != -1) ? new_nearest : 0); 
}