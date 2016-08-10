/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 09:43:40 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/10 22:56:38 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

int		quit_w(void)
{
	exit(1);
	return (1);
}

t_obj	*obj_to_move(t_scene *s, double x1, double y1, t_ray r)
{
	t_obj	*tmp;
	double	nearest;

	tmp = NULL;
	r.dir = new_vector((int)x1 - W_X / 2.0, W_Y / 2.0 - (int)y1, (W_Y / 2.0) / tan(70*0.5));
	r.dir = vector_normalize(r.dir);
	nearest = lenray(s, &r);
	if (r.obj)
		tmp = r.obj;
	printf("nearest ==\e[0;32m %lf name == %s\e[0;0m\n", nearest, "plop");
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
	s->to_move = obj_to_move(s->sc, x, y, r);
	if (s->to_move)
		ft_printf("Object == [{CBLUE%s}]\n", s->to_move->name);
	else
		ft_printf("Object not exist\n");
	return (1);
}