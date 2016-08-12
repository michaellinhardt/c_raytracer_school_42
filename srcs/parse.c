/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 19:49:55 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/12 00:18:28 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*name(int fd) 
{
	char	*line;
	char	*tmp;
	int		i;
	int		j;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && (tmp = ft_strtrim(line))
		&& !ft_strncmp(tmp, "name {", 6))
		if (verif_str(tmp, 1))
		{
			i = ft_strlen(ft_strchr(tmp, '{')) - 1;
			j = ft_strlen(ft_strchr(tmp, '}')) ;
			ft_strdel(&line);
			(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
			? error(2, "Malloc") : 1;
			ft_strdel(&tmp);
			(!(tmp = ft_strtrim(line))) ? error(2, "Malloc") : 1;
			ft_strdel(&line);
			return (tmp);
		}
		else
			error(1, "name");
	else
		error(1, "name");
	return (NULL);
}

static void	spot(int fd, t_spot **spot) 
{
	t_spot *tmp;
	t_spot *temp;

	(!(tmp = ft_memalloc(sizeof(t_spot)))) ? error(2, "Malloc") : 1;
	camera(fd, tmp->pos, 0);
	color(fd, &tmp->c_s, 1);
	if (!*spot)
		*spot = tmp;
	else
	{
		temp = *spot;
		while (temp->next)
			temp = temp->next;
		temp->next = tmp;
		// tmp->next = *spot;
		// *spot = tmp;
	}
}

int type(int fd)
{
	char	*tmp;
	char	*line;
	int		i;
	int		j;
	
	line = NULL;
	if (get_next_line(fd, &line) > 0 && ft_strstr(line, "type {") && verif_str(line, 1))
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		i = ft_strlen(ft_strchr(tmp, '{')) - 1;
		j = ft_strlen(ft_strrchr(tmp, '}')) ;
		(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j))) ? error(2, "Malloc") : 1;
		ft_strdel(&tmp);
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		if (ft_strequ(tmp, "sphere"))
		{
			ft_strdel(&tmp);
			return (SPHERE);
		}
		else if (ft_strequ(tmp, "rectangle"))
		{
			ft_strdel(&tmp);
			return (RECTANGLE);
		}
		else if (ft_strequ(tmp, "plan"))
		{
			ft_strdel(&tmp);
			return (PLAN);
		}
		else if (ft_strequ(tmp, "cone"))
		{
			ft_strdel(&tmp);
			return (CONE);
		}
		else if (ft_strequ(tmp, "cylindre"))
		{
			ft_strdel(&tmp);
			return (CYLINDRE);
		}
		else if (ft_strequ(tmp, "torus"))
		{
			ft_strdel(&tmp);
			return (TORUS);
		}
		else if (ft_strequ(tmp, "para"))
		{
			ft_strdel(&tmp);
			return (BOLOID);
		}
		else if (ft_strequ(tmp, "triangle"))
		{
			ft_strdel(&tmp);
			return (TRIANGLE);
		}
		else
			error(3, "type object");
	}
	else
		error(1, "type object");
	return ('p');
}

static void	scene(t_gen *s, int fd, t_scene *tmp) 
{
	char	*line;
	t_spot	*temp;

	(!tmp) ? error(2, "Malloc") : 1;
	tmp->name = name(fd);
	tmp->next = NULL;
	camera(fd, tmp->cam, 0);
	tmp->spot = NULL;
	s->nb++;
	tmp->nb = s->nb;
	line = NULL;
	while (get_next_line(fd, &line) > 0 && ft_strstr(line, "spot {"))
	{
		ft_strdel(&line);
		spot(fd, &tmp->spot);
	}
	if (!line || (line && !ft_strstr(line, "ambiance {")) || !tmp->spot)
		error(3, "spot");
	ambiance(tmp->amb, line);
	objects(tmp, fd, NULL);
	ft_strdel(&line);

	if (DEBUG)
	{
		ft_printf("\nscene_name == {CGREEN %s}\n", tmp->name);
		printf("\tpos cam_scene == \e[0;32m %lf %lf %lf\e[0;0m\n", tmp->cam[0], tmp->cam[1], tmp->cam[2]);
		printf("\tdir cam_scene == \e[0;32m %lf %lf %lf\e[0;0m\n", tmp->cam[3], tmp->cam[4], tmp->cam[5]);
		temp = tmp->spot;
		while (temp)
		{
			printf("\t\tpos cam_spot == \e[0;32m %lf %lf %lf\e[0;0m\n", temp->pos[0], temp->pos[1], temp->pos[2]);
			printf("\t\tdir cam_spot == \e[0;32m %lf %lf %lf\e[0;0m\n", temp->pos[3], temp->pos[4], temp->pos[5]);
			ft_printf("\t\tcolor_spot == {CGREEN%#x}\n", temp->c_s);
			temp = temp->next;
		}
		ft_printf("\t color_amb == {CGREEN%#x} inten_amb == {CGREEN%d}\n", tmp->amb[0], tmp->amb[1]);
		ft_printf("\n");
	}
	if (!s->sc)
		s->sc = tmp;
	else
	{
		tmp->next = s->sc;
		s->sc = tmp;
	}
}

void		parse_scene(t_gen *s, char *argv)
{
	int		fd;
	char	*line;
	int		ret;
	char	*tmp;
	int		a;

	fd = open(argv, O_RDONLY);
	if (fd < 0 || !ft_strstr(argv, ".rt")
		|| ft_strlen(ft_strstr(argv, ".rt")) != 3)
		return (error(0, NULL));
	a = -1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		if (ft_strequ(tmp, "scene {") && (a != 0))
		{
			scene(s, fd, ft_memalloc(sizeof(t_scene)));
			a = 0;
		}
		else if (s->sc && ft_strequ(tmp, "}") && !a)
			a = 1;
		else
			(a < 0) ? error(1, "scene") : error(3, "scene");
		ft_strdel(&tmp);
	}
	if (!a)
		error(3, "scene");
	ft_strdel(&line);
	ft_strdel(&tmp);
	if (ret < 0)
		return (error(0, NULL));
}
