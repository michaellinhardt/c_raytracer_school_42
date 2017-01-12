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

/* to del
int			usage(int fd)
{
	char *line;

	if (fd < 0)
		return (0);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line);
		free(line);
		line = NULL;
	}
	return (1);
}
*/

static void	init_struct(t_gen *s)
{
	// char		*line;

	// line = NULL;
	// ft_strdel(&line);
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

int		main(void)
{
	t_gen	s;

	s.view_angle[0] = 0;
	s.view_angle[1] = 0;
	s.view_angle[2] = 0;
	init_struct(&s);
	mlx_start(&s, &s.mlx);

/*
** void 	parse_scene(t_gen *s, char *argv) ; argv = nom du fichier ; ajouter au debut de la liste chainee
**
** void		raytracing(t_gen *s) ; lance le raytracer sur le premier maillon t_scene de t_gen
*/

	return (0);
}
