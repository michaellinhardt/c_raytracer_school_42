/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 05:39:29 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/17 19:47:05 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"

static void	print_type(t_gen *s, char **to_print, char type)
{
	char *tmp;

	tmp = *to_print;
	(void)s;
	if (type & RECTANGLE)
		*to_print = ft_strjoin(*to_print, "rectangle }\n");
	if (type & SPHERE)
		*to_print = ft_strjoin(*to_print, "sphere }\n");
	if (type & PLAN)
		*to_print = ft_strjoin(*to_print, "plan }\n");
	if (type & CONE)
		*to_print = ft_strjoin(*to_print, "cone }\n");
	if (type & CYLINDRE)
		*to_print = ft_strjoin(*to_print, "cylindre }\n");
	if (type & COMPLEXE)
		*to_print = ft_strjoin(*to_print, "complexe }\n");
	if (type & TORUS)
		*to_print = ft_strjoin(*to_print, "torus }\n");
	if (type & BOLOID)
		*to_print = ft_strjoin(*to_print, "para }\n");
	if (type & TRIANGLE)
		*to_print = ft_strjoin(*to_print, "triangle }\n");
	ft_strdel(&tmp);
}

static void	print_cam(t_gen *s, char **to_print, double *cam, char c)
{
	char *tmp;
	char *temp;
	int i;

	(void)s;
	tmp = *to_print;
	if (!c)
		*to_print = ft_strjoin(*to_print, "camera {pos{");
	else
		*to_print = ft_strjoin(*to_print, "cut {pos{");
	ft_strdel(&tmp);
	i = 0;
	while (i < 3)
	{ 
		tmp = *to_print;
		temp = ft_putfloat(cam[i], 0);
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&tmp);
		ft_strdel(&temp);
		tmp = *to_print;
		if (i != 2)
			*to_print = ft_strjoin(*to_print, ";");
		else
			*to_print = ft_strjoin(*to_print, "}, dir{");
		ft_strdel(&tmp);
		++i;
	}
	while (i < 6)
	{ 
		tmp = *to_print;
		temp = ft_putfloat(cam[i], 0);
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&tmp);
		ft_strdel(&temp);
		tmp = *to_print;
		if (i != 5)
			*to_print = ft_strjoin(*to_print, ";");
		else
		{
			*to_print = ft_strjoin(*to_print, "}}\n");
			break ;
		}
		ft_strdel(&tmp);
		++i;
	}
	ft_strdel(&tmp);
	ft_strdel(&temp);
}

static void	print_col(t_gen *s, char **to_print, int col)
{
	char *tmp;
	char *temp;

	(void)s;
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "color { 0x");
	ft_strdel(&tmp);
	tmp = *to_print;
	if ((col & 0xff0000))
	{
		temp = ft_itoa_base((col & 0xff0000) >> 16, 16, 0);
		if (ft_strlen(temp) != 2)
		{
			*to_print = ft_strjoin(*to_print, "0");
			ft_strdel(&tmp);
			tmp = *to_print;
		}
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&temp);
	}
	else
		*to_print = ft_strjoin(*to_print, "00");
	ft_strdel(&tmp);
	tmp = *to_print;
	if ((col & 0xff00))
	{
		temp = ft_itoa_base((col & 0xff00) >> 8, 16, 0);
		if (ft_strlen(temp) != 2)
		{
			*to_print = ft_strjoin(*to_print, "0");
			ft_strdel(&tmp);
			tmp = *to_print;
		}
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&temp);
	}
	else
		*to_print = ft_strjoin(*to_print, "00");
	ft_strdel(&tmp);
	tmp = *to_print;
	if ((col & 0xff))
	{
		temp = ft_itoa_base((col & 0xff), 16, 0);
		if (ft_strlen(temp) != 2)
		{
			*to_print = ft_strjoin(*to_print, "0");
			ft_strdel(&tmp);
			tmp = *to_print;
		}
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&temp);
	}
	else
		*to_print = ft_strjoin(*to_print, "00");
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " }\n");
	ft_strdel(&tmp);
}

static void	print_text(t_gen *s, char **to_print, int col)
{
	char *tmp;

	(void)s;
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "texture { ");
	if (col & EARTH)
		*to_print = ft_strjoin(*to_print, "texture { earth }");
	else if (col & FIRE)
		*to_print = ft_strjoin(*to_print, "texture { fire }");
	else if (col & BLACK)
		*to_print = ft_strjoin(*to_print, "texture { black }");
	else if (col & ICE)
		*to_print = ft_strjoin(*to_print, "texture { ice }");
	ft_strdel(&tmp);
}

static void	print_size_eff(t_gen *s, char **to_print, double *size, char c)
{
	char	*tmp;
	char	*temp;
	int		i;

	(void)s;
	tmp = *to_print;
	if (!c)
		*to_print = ft_strjoin(*to_print, "size {");	
	else
		*to_print = ft_strjoin(*to_print, "effect {");	
	ft_strdel(&tmp);
	i = 0;
	while (i < 3 + c)
	{ 
		tmp = *to_print;
		temp = ft_putfloat(size[i], 0);
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&tmp);
		ft_strdel(&temp);
		tmp = *to_print;
		if (i != 3 + c - 1)
			*to_print = ft_strjoin(*to_print, ";");
		else
			*to_print = ft_strjoin(*to_print, "}\n");
		ft_strdel(&tmp);
		++i;
	}
}

static void	print_simple(t_gen *s, char **to_print, t_obj *obj, char c)
{
	char *tmp;

	tmp = *to_print;
	if (!c)
	{
		*to_print = ft_strjoin(*to_print, "simple_obj {\n\tname { ");	
		ft_strdel(&tmp);
		tmp = *to_print;
		*to_print = ft_strjoin(*to_print, obj->name);	
		ft_strdel(&tmp);
		tmp = *to_print;
		*to_print = ft_strjoin(*to_print, " }\n");	
	}
	else
		*to_print = ft_strjoin(*to_print, "simple_obj {\n");	
	ft_strdel(&tmp);
	print_cam(s, to_print, obj->pos, 0);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "type { ");	
	ft_strdel(&tmp);
	print_type(s, to_print, obj->type);
	print_size_eff(s, to_print, obj->size, 0);
	print_size_eff(s, to_print, obj->eff, 1);
	if (!obj->text)
		print_col(s, to_print, obj->c_o);
	else
		print_text(s, to_print, obj->text);
	print_cam(s, to_print, obj->cut, 1);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "}\n");	
	ft_strdel(&tmp);
}
static void	print_complexe(t_gen *s, char **to_print, t_obj *obj)
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

static void	print_amb(t_gen *s, char **to_print, int col)
{
	char *tmp;
	char *temp;

	(void)s;
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "ambiance { 0x");
	ft_strdel(&tmp);
	tmp = *to_print;
	if ((col & 0xff0000))
	{
		temp = ft_itoa_base((col & 0xff0000) >> 16, 16, 0);
		if (ft_strlen(temp) != 2)
		{
			*to_print = ft_strjoin(*to_print, "0");
			ft_strdel(&tmp);
			tmp = *to_print;
		}
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&temp);
	}
	else
		*to_print = ft_strjoin(*to_print, "00");
	ft_strdel(&tmp);
	tmp = *to_print;
	if ((col & 0xff00))
	{
		temp = ft_itoa_base((col & 0xff00) >> 8, 16, 0);
		if (ft_strlen(temp) != 2)
		{
			*to_print = ft_strjoin(*to_print, "0");
			ft_strdel(&tmp);
			tmp = *to_print;
		}
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&temp);
	}
	else
		*to_print = ft_strjoin(*to_print, "00");
	ft_strdel(&tmp);
	tmp = *to_print;
	if ((col & 0xff))
	{
		temp = ft_itoa_base((col & 0xff), 16, 0);
		if (ft_strlen(temp) != 2)
		{
			*to_print = ft_strjoin(*to_print, "0");
			ft_strdel(&tmp);
			tmp = *to_print;
		}
		*to_print = ft_strjoin(*to_print, temp);
		ft_strdel(&temp);
	}
	else
		*to_print = ft_strjoin(*to_print, "00");
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " ; ");
	ft_strdel(&tmp);
	tmp = *to_print;
	temp = ft_itoa(s->sc->amb[1]);
	*to_print = ft_strjoin(*to_print, temp);
	ft_strdel(&tmp);
	ft_strdel(&temp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " }\n");
	ft_strdel(&tmp);
}


void	print_scene(t_gen *s)
{
	char *to_print;
	char *tmp;
	t_spot *spot;
	t_obj *obj;
	int fd;

	if (!s->sc)
		return ;
	if (access("scene", R_OK | W_OK) < 0)
		system("mkdir scene");
	tmp = ft_strjoin("./scene/", s->sc->name);
	to_print = ft_strjoin(tmp, ".rt");
	fd = open(to_print, O_CREAT | O_RDWR | O_TRUNC, 0755);
	ft_strdel(&tmp);
	ft_strdel(&to_print);
	to_print = ft_strdup("scene {\n\tname {");
	tmp = to_print;
	to_print = ft_strjoin(to_print, s->sc->name);
	ft_strdel(&tmp);
	tmp = to_print;
	to_print = ft_strjoin(to_print, "}\n");
	ft_strdel(&tmp);
	print_cam(s, &to_print, s->sc->cam, 0);
	spot = s->sc->spot;
	while (spot)
	{
		tmp = to_print;
		to_print = ft_strjoin(to_print, "spot {\n");
		ft_strdel(&tmp);
		print_cam(s, &to_print, spot->pos,0);
		print_col(s, &to_print, spot->c_s);
		tmp = to_print;
		to_print = ft_strjoin(to_print, "}\n");
		ft_strdel(&tmp);
		spot = spot->next;
	}
	print_amb(s, &to_print, s->sc->amb[0]);
	tmp = to_print;
	to_print = ft_strjoin(to_print, "objects {\n");
	ft_strdel(&tmp);
	obj = s->sc->obj;
	while (obj)
	{
		if (!(obj->type & COMPLEXE))
			print_simple(s, &to_print, obj,0);
		else
			print_complexe(s, &to_print, obj);
		obj = obj->next;		
	}
	tmp = to_print;
	to_print = ft_strjoin(to_print, "}\n}\n");
	ft_strdel(&tmp);
	write(fd, to_print, ft_strlen(to_print));
	ft_strdel(&to_print);
	close(fd);
}
