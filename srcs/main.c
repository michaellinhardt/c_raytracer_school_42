/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:09:09 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/04 21:56:59 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raytra_gen.h"
#include <h_gui.h>

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
	s->sc = NULL;
	s->to_move = NULL;
	s->nb = 0;
	s->rep = 0;
}

int		main(int argc, char **argv)
{
	t_gen s;
	t_gui_handler	*handler;

	if (argc == 1)
		return (usage(open("resources/doc.txt", O_RDONLY)));
	init_struct(&s);
	parse_scene(&s, argv);
	raytracing(&s);
	handler = NULL;
	if (!(handler = gui_create()))
	{
		ft_putstr_fd("Unable to open GTK GUI.\n", 2);
		return (-1);
	}
	gui_init(handler);
	/*
	 ** Launch GUI section. 
	 */
	// while (1);
	return (0);
}
