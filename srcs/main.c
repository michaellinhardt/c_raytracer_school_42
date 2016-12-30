/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:09:09 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/30 22:42:45 by ocarta-l         ###   ########.fr       */
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

static void	init_mlx(t_gen *s)
{
	if (!(s->mlx.mlx = mlx_init()))
		error(2, "Mlx");
	if (!(s->mlx.win = mlx_new_window(s->mlx.mlx, W_X, W_Y, "Awesome Playlist - FDF")))
		error(2, "Mlx");
	// if (!(s->mlx.img = mlx_new_image(s->mlx.mlx, W_X, W_Y)))
	// 	error(2, "Mlx");
}

static void	init_struct(t_gen *s)
{
	char		*line;

	line = NULL;
	ft_strdel(&line);
	texture_earth(0, 0, "oui", s->mlx.mlx);
	texture_fire(0, 0, "oui", s->mlx.mlx);
	texture_black(0, 0, "oui", s->mlx.mlx);
	texture_ice(0, 0, "oui", s->mlx.mlx);
	s->sc = NULL;
	s->nb = 0;
	s->rep = 0;
}

int		main(void)
{
	t_gen	s;

	s.view_angle[0] = 0;
	s.view_angle[1] = 0;
	s.view_angle[2] = 0;
	init_mlx(&s);
	init_struct(&s);

/*
** void 	parse_scene(t_gen *s, char *argv) ; argv = nom du fichier ; ajouter au debut de la liste chainee
**
** void		raytracing(t_gen *s) ; lance le raytracer sur le premier maillon t_scene de t_gen
*/

	mlx_loop(s.mlx.mlx);
	return (0);
}
