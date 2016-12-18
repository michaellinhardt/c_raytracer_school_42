/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:43:52 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 07:27:16 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char				*parse_vertex(int fd, char *l, t_line **v)
{
	t_line	*temp;
	char	*tmp;

	while (l && l[0] == 'v' && l[1] == ' ' && ft_strchr_c(l, ' ') >= 3)
	{
		(!(temp = ft_memalloc(sizeof(t_line)))) ? error(2, "Malloc") : 1;
		temp->str = ft_strdup(l + 2);
		ft_strdel(&l);
		add_list(v, temp);
		get_next_line(fd, &l);
		tmp = ft_strtrim(l);
		ft_strdel(&l);
		while (!tmp[0] || tmp[0] == '#' || tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			get_next_line(fd, &l);
			tmp = ft_strtrim(l);
			ft_strdel(&l);
		}
		l = tmp;
	}
	if (!l || l[0] != 'v' || !l[1] || l[1] != 'n' || !l[2] || l[2] != ' ')
		error(3, "objects");
	return (l);
}

char				*parse_vnormal(int fd, char *l, t_line **v)
{
	t_line	*temp;
	char	*tmp;

	while (l && l[0] == 'v' && l[1] == 'n' && l[2] == ' '
		&& ft_strchr_c(l, ' ') >= 3)
	{
		(!(temp = ft_memalloc(sizeof(t_line)))) ? error(2, "Malloc") : 1;
		temp->str = ft_strdup(l + 3);
		ft_strdel(&l);
		add_list(v, temp);
		get_next_line(fd, &l);
		tmp = ft_strtrim(l);
		ft_strdel(&l);
		while (!tmp[0] || tmp[0] == '#' || tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			get_next_line(fd, &l);
			tmp = ft_strtrim(l);
			ft_strdel(&l);
		}
		l = tmp;
	}
	if (!l || l[0] != 'f' || !l[1] || l[1] != ' ')
		error(3, "objects");
	return (l);
}

void				init_tab(t_line *v, double tab[][3])
{
	int		i[2];
	char	**tmp;
	char	*temp;

	i[0] = 1;
	while (v && (i[1] = -1))
	{
		tmp = ft_strsplit(v->str, ' ');
		while (tmp[++i[1]] && i[1] < 3)
		{
			temp = ft_strtrim(tmp[i[1]]);
			if (verif_double(temp))
				tab[i[0]][i[1]] = ft_atob(temp);
			else
				error(3, "obijects");
			ft_strdel(&temp);
			ft_strdel(&tmp[i[1]]);
		}
		if (++i[0] && i[1] != 3)
			error(3, "objects");
		free(tmp);
		tmp = NULL;
		ft_strdel(&v->str);
		v = v->next;
	}
}

void				parse_f(t_line **v, char *tmp, t_obj **o, int fd)
{
	double		nbr_v[len_lst(v[0]) + 2][3];
	double		nbr_vn[len_lst(v[1]) + 2][3];
	double		nbr[2][10000][3];

	nbr_v[0][0] = len_lst(v[0]);
	init_tab(v[0], nbr_v);
	nbr_vn[0][0] = len_lst(v[1]);
	init_tab(v[1], nbr_vn);
	ft_memcpy(nbr[0], nbr_v, sizeof(double **) * (len_lst(v[0]) + 2) * 3);
	ft_memcpy(nbr[1], nbr_vn, sizeof(double **) * (len_lst(v[1]) + 2) * 3);
	free_lst(v[0]);
	free_lst(v[1]);
	add_vector(nbr, o, tmp, fd);
}

void				triangle(int fd, t_obj **o, char *line)
{
	char	*tmp;
	t_line	*v[2];

	if (get_next_line(fd, &line) < 0 || !ft_strstr(line, "{"))
		error(3, "objects");
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		if (!tmp[0] || tmp[0] == '#' || tmp[0] == 'o'
			|| tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			continue ;
		}
		if (tmp[0] == 'v' && tmp[1] && tmp[1] == ' ' && !(v[0] = NULL))
			break ;
		error(3, "objects");
	}
	line = parse_vertex(fd, tmp, &v[0]);
	v[1] = NULL;
	tmp = parse_vnormal(fd, line, &v[1]);
	parse_f(v, tmp, o, fd);
}
