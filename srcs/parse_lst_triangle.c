/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 01:59:50 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 04:41:31 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void				free_lst(t_line *lst)
{
	if (lst)
	{
		if (lst->next)
			free_lst(lst->next);
		free(lst);
		lst = NULL;
	}
}

int					len_lst(t_line *l)
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

void				add_list_bis(t_obj **v, t_obj *temp)
{
	t_obj *t;

	t = *v;
	if (!t)
		*v = temp;
	else
		add_list_bis((t_obj **)&t->next, temp);
}

void				add_list(t_line **v, t_line *temp)
{
	t_line *t;

	t = *v;
	if (!t)
		*v = temp;
	else
		add_list((t_line **)&t->next, temp);
}

void				color_text(char *str, t_obj *o)
{
	char *tmp;

	tmp = ft_strsub(str, 9, ft_strlen(str) - 10);
	ft_strdel(&str);
	str = ft_strtrim(tmp);
	ft_strdel(&tmp);
	if (ft_strequ(str, "earth"))
		o->text ^= EARTH;
	else if (ft_strequ(str, "fire"))
		o->text ^= FIRE;
	else if (ft_strequ(str, "black"))
		o->text ^= BLACK;
	else if (ft_strequ(str, "ice"))
		o->text ^= ICE;
	else
		error(3, "color");
	ft_strdel(&str);
}
