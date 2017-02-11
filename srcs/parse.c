/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 19:49:55 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 02:31:03 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char			*name(int fd)
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
			j = ft_strlen(ft_strchr(tmp, '}'));
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

static void		spot(int fd, t_spot **spot)
{
	t_spot *tmp;
	t_spot *temp;

	(!(tmp = ft_memalloc(sizeof(t_spot)))) ? error(2, "Malloc") : 1;
	tmp->name = name(fd);
	tmp->type ^= type_spot(fd);
	camera(fd, tmp->pos, 0);
	color(fd, &tmp->c_s, 1, NULL);
	if (!*spot)
		*spot = tmp;
	else
	{
		temp = *spot;
		while (temp->next)
			temp = temp->next;
		temp->next = tmp;
	}
}

static void		scene(t_gen *s, int fd, t_scene *tmp)
{
	char	*line;

	(!tmp) ? error(2, "Malloc") : 1;
	tmp->name = name(fd);
	camera(fd, tmp->cam, 0);
	tmp->spot = NULL;
	tmp->nb = ++s->nb;
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
	if (!s->sc)
		s->sc = tmp;
	else
	{
		tmp->next = s->sc;
		s->sc = tmp;
	}
}

void			parse_scene(t_gen *s, char *argv)
{
	int		fd;
	char	*line;
	int		ret;
	char	*tmp;
	int		a;

	fd = open(argv, O_RDONLY);
	if (fd < 0 || !ft_strstr(argv, ".rt") || !(a = -1)
		|| ft_strlen(ft_strstr(argv, ".rt")) != 3)
		return (error(0, NULL));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		if (ft_strequ(tmp, "scene {") && (a != 0) && !(a = 0))
			scene(s, fd, ft_memalloc(sizeof(t_scene)));
		else if (s->sc && ft_strequ(tmp, "}") && !a)
			a = 1;
		ft_strdel(&tmp);
	}
	if (ret < 0)
		return (error(0, NULL));
	(a != 1) ? error(3, "scene") : 1;
	ft_strdel(&line);
	ft_strdel(&tmp);
}
