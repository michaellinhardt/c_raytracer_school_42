/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:09:09 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 18:33:41 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"
#include <gui.h>

int		usage(int fd)
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

void	init_struct(t_gen *s)
{
	static void	*mlx;
	char		*line;

	mlx = mlx_init();
	line = NULL;
	ft_strdel(&line);
	texture_earth(0, 0, "oui", mlx);
	texture_fire(0, 0, "oui", mlx);
	texture_black(0, 0, "oui", mlx);
	texture_ice(0, 0, "oui", mlx);
	s->sc = NULL;
	s->to_move = NULL;
	s->nb = 0;
	s->rep = 0;
}

int		main(void)
{
	t_gen s;

	s.view_angle[0] = 0;
	s.view_angle[1] = 0;
	s.view_angle[2] = 0;
	load_interface(&s);
	init_struct(&s);
	gtk_widget_show_all(s.pwindow);
	gtk_main();
	return (0);
}
