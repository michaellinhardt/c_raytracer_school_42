/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:09:09 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/17 17:11:32 by ocarta-l         ###   ########.fr       */
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
	static void *mlx;
	char *line;

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

int		main(int argc, char **argv)
{
	t_gen s;

	(void)argv;
	load_interface(&s);
	init_struct(&s);
	parse_scene(&s, argv[1]);
	if (argc == 1)
		return (usage(open("resources/doc.txt", O_RDONLY)));
	raytracing(&s);
	gtk_main();
	return (0);
}
