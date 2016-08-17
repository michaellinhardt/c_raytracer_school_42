/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:43:52 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/17 19:37:24 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void add_list_bis(t_obj **v, t_obj *temp)
{
	t_obj *t;

	t = *v;
	if (!t)
		*v = temp;
	else
		add_list_bis((t_obj **)&t->next, temp);
}

void add_list(t_line **v, t_line *temp)
{
	t_line *t;

	t = *v;
	if (!t)
		*v = temp;
	else
		add_list((t_line **)&t->next, temp);
}

char *parse_vertex(int fd, char *line, t_line **v)
{
	t_line *temp;
	char *tmp;

	while (line && line[0] == 'v' && line[1] == ' ' && ft_strchr_c(line, ' ') >= 3)
	{
		(!(temp = ft_memalloc(sizeof(t_line)))) ? error(2, "Malloc") : 1;
		temp->str = ft_strdup(line + 2);
		ft_strdel(&line);
		add_list(v, temp);
		get_next_line(fd, &line);
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		while (!tmp[0] || tmp[0] == '#' || tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			get_next_line(fd, &line);
			tmp = ft_strtrim(line);
			ft_strdel(&line);
		}
		line = tmp;
	}
	if (!line || line[0] != 'v' || !line[1] || line[1] != 'n' || !line[2] || line[2] != ' ')
		error(3, "objects");
	return (line);
}

char *parse_vnormal(int fd, char *line, t_line **v)
{
	t_line *temp;
	char *tmp;

	while (line && line[0] == 'v' && line[1] == 'n' && line[2] == ' ' && ft_strchr_c(line, ' ') >= 3)
	{
		(!(temp = ft_memalloc(sizeof(t_line)))) ? error(2, "Malloc") : 1;
		temp->str = ft_strdup(line + 3);
		ft_strdel(&line);
		add_list(v, temp);
		get_next_line(fd, &line);
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		while (!tmp[0] || tmp[0] == '#' || tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			get_next_line(fd, &line);
			tmp = ft_strtrim(line);
			ft_strdel(&line);
		}
		line = tmp;
	}
	if (!line || line[0] != 'f' || !line[1] || line[1] != ' ')
		error(3, "objects");
	return (line);
}

int len_lst(t_line *l)
{
	int i;

	i = 0;
	while (l)
	{
		l = l->next;
		++i;
	}
	return (i);
}

void init_tab(t_line *v, double tab[][3])
{
	int i;
	int j;
	char **tmp;
	char *temp;

	i = 1;
	while (v)
	{
		j = 0;
		tmp = ft_strsplit(v->str, ' ');
		while (tmp[j] && j < 3)
		{
			temp = ft_strtrim(tmp[j]);
			if (verif_double(temp))
				tab[i][j] = ft_atob(temp);
			else
				error(3, "objects");
			ft_strdel(&temp);
			ft_strdel(&tmp[j]);
			++j;
		}
		if (j != 3)
			error(3, "objects");
		free(tmp);
		tmp = NULL;
		ft_strdel(&v->str);
		++i;
		v = v->next;
	}
}

void	free_lst(t_line *lst)
{
	if (lst)
	{
		if (lst->next)
			free_lst(lst->next);
		free(lst);
		lst = NULL;
	}
}

void 	add_vector(double nbr_vn[][3], double nbr_v[][3], t_obj **o, char *line, int fd)
{
	char **temp;
	char *tmp; 
	int i;
	t_obj *triangle;

	while (line && line[0] == 'f' && line[1] && line[1] == ' ')
	{
		tmp = ft_strdup(line + 2);
		ft_strdel(&line);
		temp = ft_strsplit(tmp, ' ');
		ft_strdel(&tmp);
		i = 0;
		(!(triangle = ft_memalloc(sizeof(t_obj)))) ? error(2, "Malloc") : 1;
		while (temp[i] && ft_strchr(temp[i], '/'))
		{
			tmp = ft_strtrim(temp[i]);
			line = ft_strsub(tmp, 0, ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '/')));
			if (verif_double(line))
			{
				if (ft_atoi(line) > nbr_v[0][0])
					error(3, "vector information");
				triangle->tri[i].x = (nbr_v[ft_atoi(line)][0]) * 5	 + (*o)->pos[0];
				triangle->tri[i].y = (nbr_v[ft_atoi(line)][1]) * 5	 + (*o)->pos[1];
				triangle->tri[i].z = (nbr_v[ft_atoi(line)][2]) * 5	 + (*o)->pos[2];
				ft_strdel(&line);
				if (i == 2)
				{
					line = ft_strsub(tmp, ft_strlen(tmp) - ft_strlen(ft_strrchr(tmp, '/')) + 1, ft_strlen(tmp));
					if (verif_double(line))
					{
						if (ft_atoi(line) > nbr_vn[0][0])
							error(3, "normal information");
						triangle->nor.x = nbr_vn[ft_atoi(line)][0];
						triangle->nor.y = nbr_vn[ft_atoi(line)][1];
						triangle->nor.z = nbr_vn[ft_atoi(line)][2];
						ft_strdel(&line);
					}
					else
						error(3, "objects");
				}
				ft_strdel(&tmp);
			}
			else
				error(3, "objects");
			ft_strdel(&temp[i]);
			++i;
		}
		free(temp);
		temp = NULL;
		if (i != 3)
			error(3, "objects");
		add_list_bis(&(*o)->comp, triangle);
		get_next_line(fd, &line);
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		while (!tmp[0] || tmp[0] == '#' || tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			get_next_line(fd, &line);
			tmp = ft_strtrim(line);
			ft_strdel(&line);
		}
		line = tmp;
	}
	if (!line || !ft_strchr(line, '}'))
		error(3, "objects");
	ft_strdel(&line);
}

void	parse_f(t_line *v, t_line *vn, char *tmp, t_obj **o, int fd)
{
	double		nbr_v[len_lst(v) + 2][3];
	double		nbr_vn[len_lst(vn) + 2][3];

	nbr_v[0][0] = len_lst(v);
	init_tab(v, nbr_v);
	nbr_vn[0][0] = len_lst(vn);
	init_tab(vn, nbr_vn);
	free_lst(v);
	free_lst(vn);
	add_vector(nbr_vn, nbr_v, o, tmp, fd);
	if (DEBUG)
	{
		t_obj *t = (*o)->comp;
		ft_printf("________________________________________________________________________\n");
		while (t)
		{
			printf("vector 1 = %lf %lf %lf\n", t->tri[0].x,t->tri[0].y,t->tri[0].z);
			printf("vector 2 = %lf %lf %lf\n", t->tri[1].x,t->tri[1].y,t->tri[1].z);
			printf("vector 3 = %lf %lf %lf\n", t->tri[2].x,t->tri[2].y,t->tri[2].z);
			printf("norm = %lf %lf %lf\n\n", t->nor.x,t->nor.y,t->nor.z);
			t = t->next;
		}
	}	
}

void	triangle(int fd, t_obj **o, char *line)
{
	char *tmp;
	t_line	*v;
	t_line	*vn;

	if (get_next_line(fd, &line) < 0 || !ft_strstr(line, "{"))
		error(3, "objects");
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		if (!tmp[0])
		{
			ft_strdel(&tmp);
			continue ;
		}
		if (tmp[0] == '#' || tmp[0] == 'o' || tmp[0] == 'g' || tmp[0] == 's')
		{
			ft_strdel(&tmp);
			continue ;
		}
		if (tmp[0] == 'v' && tmp[1] && tmp[1] == ' ')
			break ;
		error(3, "objects");
	}
	v = NULL;
	line = parse_vertex(fd, tmp, &v);
	vn = NULL;
	tmp = parse_vnormal(fd, line, &vn);
	parse_f(v, vn, tmp, o, fd);
	(void)o;
	(void)vn;
}
