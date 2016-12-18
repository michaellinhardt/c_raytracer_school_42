/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 05:39:29 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 07:24:42 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"

static void			print_simple_first(char c, char **to_print,
	char **tmp, t_obj *obj)
{
	if (!c)
	{
		*to_print = ft_strjoin(*to_print, "simple_obj {\n\tname { ");
		ft_strdel(tmp);
		*tmp = *to_print;
		*to_print = ft_strjoin(*to_print, obj->name);
		ft_strdel(tmp);
		*tmp = *to_print;
		*to_print = ft_strjoin(*to_print, " }\n");
	}
	else
		*to_print = ft_strjoin(*to_print, "simple_obj {\n");
	ft_strdel(tmp);
}

static void			print_simple(t_scene *s, char **to_print,
	t_obj *obj, char c)
{
	char *tmp;

	tmp = *to_print;
	print_simple_first(c, to_print, &tmp, obj);
	print_cam(s, to_print, obj->pos, 0);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "type { ");
	ft_strdel(&tmp);
	print_type(s, to_print, obj->type);
	print_size_eff(s, to_print, obj->size, 0);
	print_size_eff(s, to_print, obj->eff, 3);
	if (!obj->text)
		print_col(to_print, obj->c_o, NULL);
	else
	{
		print_text(s, to_print, obj->text);
		tmp = *to_print;
		*to_print = ft_strjoin(*to_print, "}\n");
		ft_strdel(&tmp);
	}
	(obj->cut) ? print_cut(s, to_print, obj->cut, 1) : 1;
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "}\n");
	ft_strdel(&tmp);
}

static void			print_complexe(t_scene *s, char **to_print, t_obj *obj)
{
	char *tmp;

	(void)s;
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "complex_obj {\n\tname { ");
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, obj->name);
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " }\n");
	ft_strdel(&tmp);
	print_cam(s, to_print, obj->pos, 0);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "type { ");
	ft_strdel(&tmp);
	print_type(s, to_print, obj->type);
	while (obj->comp)
	{
		print_simple(s, to_print, obj->comp, 1);
		obj->comp = obj->comp->next;
	}
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "}\n");
	ft_strdel(&tmp);
}

static void			print_first(char **tp, t_scene *s)
{
	ft_strdel(&tp[1]);
	ft_strdel(&tp[0]);
	tp[0] = ft_strdup("scene {\n\tname {");
	tp[1] = tp[0];
	tp[0] = ft_strjoin(tp[0], s->name);
	ft_strdel(&tp[1]);
	tp[1] = tp[0];
	tp[0] = ft_strjoin(tp[0], "1");
	ft_strdel(&tp[1]);
	tp[1] = tp[0];
	tp[0] = ft_strjoin(tp[0], "}\n");
	ft_strdel(&tp[1]);
	print_spot(s, &tp[0], &tp[1]);
}

void				print_scene(t_scene *s)
{
	char	*tp[2];
	t_obj	*obj;
	int		fd;

	if (!s || !(tp[1] = ft_strjoin("./scene/", s->name)))
		return ;
	(access("scene", R_OK | W_OK) < 0) ? system("mkdir scene") : 1;
	tp[0] = ft_strjoin(tp[1], ".rt");
	fd = open(tp[0], O_CREAT | O_RDWR | O_TRUNC, 0755);
	print_first(tp, s);
	obj = s->obj;
	while (obj)
	{
		(!(obj->type & COMPLEXE)) ? print_simple(s, &tp[0], obj, 0)
		: print_complexe(s, &tp[0], obj);
		obj = obj->next;
	}
	tp[1] = tp[0];
	tp[0] = ft_strjoin(tp[0], "}\n}\n");
	ft_strdel(&tp[1]);
	write(fd, tp[0], ft_strlen(tp[0]));
	ft_strdel(&tp[0]);
	close(fd);
}
