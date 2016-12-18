/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 02:08:04 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 02:09:29 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		split_cut_mid(double *cam, char *temp, char c, int *i)
{
	char **pos;
	char *tmp;

	pos = ft_strsplit(temp, ';');
	while (pos[++*i])
	{
		tmp = ft_strtrim(pos[*i]);
		ft_strdel(&pos[*i]);
		if (verif_double(tmp))
			cam[*i + c] = ft_atob(tmp);
		else
			error(3, "cut");
		ft_strdel(&tmp);
	}
	free(pos);
	pos = NULL;
	if (*i != 3)
		error(3, "cut");
}

static void		split_cut_first(double *cam, char *temp, char *tmp, char c)
{
	int		i;

	i = -1;
	if (ft_strchr_c(tmp, ';') == 2)
	{
		ft_strdel(&tmp);
		split_cut_mid(cam, temp, c, &i);
		ft_strdel(&temp);
	}
	else
		error(3, "cut");
}

static void		split_cut(double *cam, char **tab)
{
	char	*tmp;
	char	*temp;

	tmp = ft_strtrim(tab[0]);
	if (!ft_strncmp(tmp, "pos{", 4) && verif_str(tmp, 1))
	{
		temp = ft_strsub(tmp, 4, ft_strlen(tmp)
			- 4 - ft_strlen(ft_strchr(tmp, '}')));
		split_cut_first(cam, temp, tmp, 0);
		ft_strdel(&tab[0]);
	}
	else
		error(3, "cut");
	tmp = ft_strtrim(tab[1]);
	if (!ft_strncmp(tmp, "dir{", 4) && verif_str(tmp, 1))
	{
		temp = ft_strsub(tmp, 4, ft_strlen(tmp)
			- 4 - ft_strlen(ft_strchr(tmp, '}')));
		split_cut_first(cam, temp, tmp, 3);
		ft_strdel(&tab[1]);
	}
	else
		error(3, "cut");
	free(tab);
	tab = NULL;
}

static void		cut_mid(char *tmp, char *line, double *cam)
{
	char	**tab;
	int		i;
	int		j;

	if (!verif_str(tmp, 3))
		error(3, "cut");
	i = ft_strlen(ft_strchr(tmp, '{')) - 1;
	j = ft_strlen(ft_strrchr(tmp, '}'));
	ft_strdel(&line);
	(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
	? error(2, "Malloc") : 1;
	ft_strdel(&tmp);
	(!(tab = ft_strsplit(line, ','))) ? error(2, "Malloc") : 1;
	ft_strdel(&line);
	split_cut(cam, tab);
}

char			*cut(int fd, t_obj *o)
{
	char	*line;
	char	*tmp;
	t_cut	*cut;

	line = NULL;
	while (get_next_line(fd, &line) > 0 && (tmp = ft_strtrim(line))
			&& (!ft_strncmp(tmp, "cut {", 5)))
	{
		(!(cut = ft_memalloc(sizeof(t_cut)))) ? error(2, "Malloc") : 1;
		cut_mid(tmp, line, cut->pos);
		if (!o->cut)
			o->cut = cut;
		else
		{
			cut->next = o->cut;
			o->cut = cut;
		}
	}
	ft_strdel(&line);
	return (tmp);
}
