/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 09:43:40 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/26 18:54:37 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

int		quit_w(void)
{
	exit(1);
	return (1);
}

t_obj	*obj_to_move(t_obj *s, double x1, double y1, t_ray r)
{
	t_obj *tmp;
	double nearest;
	double t;
	int col = 0;
	tmp = NULL;
	nearest = -1;
	while (s)
	{
		r.dir.x = x1 - W_X / 2.0;
		r.dir.y = W_Y / 2.0 - y1 ;
		r.dir.z = (W_Y / 2.0) / tan(70*0.5);
		r.dir = vectorNormalize(r.dir);
		t = 0;
		if (s->type == SPHERE)
			t = intersectRaySphere(&r, s, &x1, &y1);
		else if (s->type == PLAN)
			t = intersectRayPlane(&r, s, &x1, &y1);
		else if (s->type == CYLINDRE)
			t = intersectRayCylindre(&r, s, &x1, &y1);
		else if (s->type == RECTANGLE)
			t = intersectRayCarre(&r, s, &x1, &y1);
		else if (s->type == COMPLEXE)
			t = intersectRayComplex(&r, s, &x1, &y1, &col);
		else if (s->type == CONE)
			t = intersectRayCone(&r, s, &x1, &y1);
		else if (s->type == TORUS)
			t = intersectRayCone(&r, s, &x1, &y1);
		else if (s->type == BOLOID)
			t = intersectRayBoloid(&r, s, &x1, &y1);
		if ((t < nearest && t > 0.00001) || (nearest < 0 && t > 0.00001))
		{
			nearest = t;
			tmp = s;
		}
		s = s->next;
	}
	printf("nearest ==\e[0;32m %lf t == %lf\e[0;0m\n", nearest, t);
	return (tmp);
}

int		mouse_functions(int button, int x, int y, t_gen *s)
{
	t_ray r;

	(void)button;
	if (x < 0 || y < 0 || x > W_X || y > W_Y || !s->sc)
		return (1);
	r.start.x = s->sc->cam[0];
	r.start.y = s->sc->cam[1];
	r.start.z = s->sc->cam[2];
	r.dir.x = s->sc->cam[3];
	r.dir.y = s->sc->cam[4];
	r.dir.z = s->sc->cam[5];
	s->to_move = obj_to_move(s->sc->obj, x, y, r);
	if (s->to_move)
		ft_printf("Object == [{CBLUE%s}]\n", s->to_move->name);
	else
		ft_printf("Object not exist\n");
	return (1);
}