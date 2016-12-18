/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vector_triangle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 01:56:46 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 02:39:24 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void			add_vn_mid(char *line, char *tmp, double nbr[2][10000][3]
	, t_obj *triangle)
{
	line = ft_strsub(tmp, ft_strlen(tmp)
		- ft_strlen(ft_strrchr(tmp, '/')) + 1, ft_strlen(tmp));
	if (verif_double(line))
	{
		if (ft_atoi(line) > nbr[1][0][0])
			error(3, "normal information");
		triangle->nor.x = nbr[1][ft_atoi(line)][0];
		triangle->nor.y = nbr[1][ft_atoi(line)][1];
		triangle->nor.z = nbr[1][ft_atoi(line)][2];
		ft_strdel(&line);
	}
	else
		error(3, "objects");
}

static void			add_v_mid(char **l, char **t, double nbr[2][10000][3])
{
	*l = ft_strsub(*t, 0, ft_strlen(*t) - ft_strlen(ft_strchr(*t, '/')));
	(!verif_double(*l)) ? error(3, "objects") : 1;
	(ft_atoi(*l) > nbr[0][0][0]) ? error(3, "vector info") : 1;
}

static void			end_loop_vector(char **line, char **tmp, int fd, char **tm)
{
	free(tm);
	tm = NULL;
	get_next_line(fd, line);
	*tmp = ft_strtrim(*line);
	ft_strdel(line);
	while (!*tmp[0] || *tmp[0] == '#' || *tmp[0] == 'g' || *tmp[0] == 's')
	{
		ft_strdel(tmp);
		get_next_line(fd, line);
		*tmp = ft_strtrim(*line);
		ft_strdel(line);
	}
	*line = *tmp;
}

static void			first_loop(char **t, char ***tm, char **l)
{
	*t = ft_strdup(*l + 2);
	ft_strdel(l);
	*tm = ft_strsplit(*t, ' ');
	ft_strdel(t);
}

void				add_vector(double nbr[2][10000][3], t_obj **o,
	char *l, int fd)
{
	char	**tm;
	char	*t;
	int		i;
	t_obj	*triangle;

	while (l && l[0] == 'f' && l[1] && l[1] == ' ' && (i = -1))
	{
		first_loop(&t, &tm, &l);
		(!(triangle = ft_memalloc(sizeof(t_obj)))) ? error(2, "Malloc") : 1;
		while (tm[++i] && ft_strchr(tm[i], '/') && (t = ft_strtrim(tm[i])))
		{
			add_v_mid(&l, &t, nbr);
			triangle->tri[i].x = (nbr[0][ft_atoi(l)][0]) * 5 + (*o)->pos[0];
			triangle->tri[i].y = (nbr[0][ft_atoi(l)][1]) * 5 + (*o)->pos[1];
			triangle->tri[i].z = (nbr[0][ft_atoi(l)][2]) * 5 + (*o)->pos[2];
			ft_strdel(&l);
			(i == 2) ? add_vn_mid(l, t, nbr, triangle) : 1;
			ft_strdel(&t);
			ft_strdel(&tm[i]);
		}
		(i != 3) ? error(3, "objects") : 1;
		add_list_bis(&(*o)->comp, triangle);
		end_loop_vector(&l, &t, fd, tm);
	}
	(!l || !ft_strchr(l, '}')) ? error(3, "objects2") : ft_strdel(&l);
}
