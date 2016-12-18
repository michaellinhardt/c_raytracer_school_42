/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 06:34:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 02:09:08 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_obj	*simple_obj(int fd, char *line, char c)
{
	t_obj *o;

	(!(o = ft_memalloc(sizeof(t_obj)))) ? error(2, "Malloc") : 1;
	if (!c)
		o->name = name(fd);
	camera(fd, o->pos, 0);
	o->type ^= type(fd);
	if (o->type != TRIANGLE)
	{
		size(fd, o->size);
		effect(fd, o->eff);
		color(fd, &o->c_o, 0, o);
		line = cut(fd, o);
	}
	else
	{
		color(fd, &o->c_o, 0, o);
		triangle(fd, &o, NULL);
	}
	return (o);
}

void			end_cmpl_obj(char **line, char **temp)
{
	if (ft_strstr(*line, "}"))
	{
		*temp = ft_strtrim(*line);
		(!ft_strequ(*temp, "}")) ? error(1, "object") : 1;
		ft_strdel(temp);
		ft_strdel(line);
	}
	else
		error(1, "object");
}

static t_obj	*cmpl_obj(int fd, char *line)
{
	t_obj	*o;
	char	*temp;
	t_obj	*t;

	(!(o = ft_memalloc(sizeof(t_obj)))) ? error(2, "Malloc") : 1;
	o->name = name(fd);
	camera(fd, o->pos, 0);
	o->type ^= COMPLEXE;
	o->comp = NULL;
	while (get_next_line(fd, &line) > 0 && ft_strstr(line, "simple_obj {"))
	{
		t = simple_obj(fd, NULL, 1);
		if (!o->comp)
			o->comp = t;
		else
		{
			t->next = o->comp;
			o->comp = t;
		}
		ft_strdel(&line);
	}
	end_cmpl_obj(&line, &temp);
	return (o);
}

static void		objects_next(t_scene *tmp, int fd, char *line)
{
	t_obj *t;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "simple_obj {"))
			t = simple_obj(fd, NULL, 0);
		else if (ft_strstr(line, "complex_obj {"))
			t = cmpl_obj(fd, NULL);
		else if (tmp->obj && ft_strstr(line, "}"))
		{
			ft_strdel(&line);
			break ;
		}
		else
			error(3, "objects");
		ft_strdel(&line);
		if (!tmp->obj)
			tmp->obj = t;
		else
		{
			t->next = tmp->obj;
			tmp->obj = t;
		}
	}
}

void			objects(t_scene *tmp, int fd, char *line)
{
	char *temp;

	get_next_line(fd, &line);
	temp = ft_strtrim(line);
	ft_strdel(&line);
	if (!ft_strequ(temp, "objects {"))
		error(1, "objects");
	ft_strdel(&temp);
	objects_next(tmp, fd, line);
}
