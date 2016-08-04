/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 06:34:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/21 07:09:05 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parse.h"


static t_obj	*simple_obj(int fd, char *line, char c)
{
	t_obj *o;
	char *temp;

	(!(o = ft_memalloc(sizeof(t_obj)))) ? error(2, "Malloc") : 1;
	if (!c)
		o->name = name(fd);
	camera(fd, o->pos, 0);
	o->type = type(fd);
	size(fd, o->size);
	effect(fd, o->eff);
	color(fd, &o->c_o, 0);
	camera(fd, o->cut, 1);
	if (get_next_line(fd, &line) > 0 && ft_strstr(line, "}"))
	{
		temp = ft_strtrim(line);
		if (!ft_strequ(temp, "}"))
			error(1, "object");
		ft_strdel(&temp);
		ft_strdel(&line);
	}
	else
		error(1, "object");
	if (DEBUG)
	{
		ft_printf("obj_simple name = {CGREEN%s}\n", o->name);
		printf("\tpos obj_simple == \e[0;32m %lf %lf %lf\e[0;0m\n", o->pos[0], o->pos[1], o->pos[2]);
		printf("\tdir obj_simple == \e[0;32m %lf %lf %lf\e[0;0m\n", o->pos[3], o->pos[4], o->pos[5]);
		ft_printf("obj_simple type = {CGREEN%d}\n", o->type);
		printf("\tobj_simple size == \e[0;32m %lf %lf %lf\e[0;0m\n", o->size[0], o->size[1], o->size[2]);
		printf("\tobj_simple effect == \e[0;32m %lf %lf %lf %lf\e[0;0m\n", o->eff[0], o->eff[1], o->eff[2], o->eff[3]);
		ft_printf("obj_simple color = {CGREEN%#x}\n", o->c_o);
		printf("\tcut pos obj_simple == \e[0;32m %lf %lf %lf\e[0;0m\n", o->cut[0], o->cut[1], o->cut[2]);
		printf("\tcut dir obj_simple == \e[0;32m %lf %lf %lf\e[0;0m\n", o->cut[3], o->cut[4], o->cut[5]);
	}
	return (o);
}

static t_obj	*cmpl_obj(int fd, char *line)
{
	t_obj 	*o;
	char 	*temp;
	t_obj *t;

	(!(o = ft_memalloc(sizeof(t_obj)))) ? error(2, "Malloc") : 1;
	o->name = name(fd);
	camera(fd, o->pos, 0);
	o->type = COMPLEXE;
	o->comp = NULL;

	get_next_line(fd, &line);
	ft_strdel(&line);
/*
	a rajouter
*/
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
	if (ft_strstr(line, "}"))
	{
		temp = ft_strtrim(line);
		if (!ft_strequ(temp, "}"))
			error(1, "object");
		ft_strdel(&temp);
		ft_strdel(&line);
	}
	else
		error(1, "object");
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
