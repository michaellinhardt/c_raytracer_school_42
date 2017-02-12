/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:09:09 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/01/07 05:00:48 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void	init_struct(t_gen *s)
{
	ft_bzero(s, sizeof(t_gen));
	texture_earth(0, 0, "oui", &s->mlx.mlx);
	texture_fire(0, 0, "oui", &s->mlx.mlx);
	texture_black(0, 0, "oui", &s->mlx.mlx);
	texture_ice(0, 0, "oui", &s->mlx.mlx);
	s->sc = NULL;
	s->sc_off = NULL;
	s->nb = 0;
	s->rep = 0;
}

int			main(void)
{
	t_gen	s;

	s.view_angle.x = 0;
	s.view_angle.y = 0;
	s.view_angle.z = 0;
	init_struct(&s);
	mlx_start(&s, &s.mlx);
	return (0);
}
