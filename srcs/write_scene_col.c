/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 07:19:15 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 07:21:15 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"

void				print_cut(t_scene *s, char **to_print, t_cut *cut, char c)
{
	while (cut)
	{
		print_cam(s, to_print, cut->pos, c);
		cut = cut->next;
	}
}

static void			print_col_mask(char **to_print, int col, int mask, int i)
{
	char *temp;
	char *tmp;

	if ((col & mask))
	{
		temp = ft_itoa_base((col & mask) >> i, 16, 0);
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
}

void				print_col(char **to_print, int col, char *tmp)
{
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "color { 0x");
	ft_strdel(&tmp);
	tmp = *to_print;
	print_col_mask(to_print, col, 0xff0000, 16);
	ft_strdel(&tmp);
	tmp = *to_print;
	print_col_mask(to_print, col, 0xff00, 8);
	ft_strdel(&tmp);
	tmp = *to_print;
	print_col_mask(to_print, col, 0xff, 0);
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " }\n");
	ft_strdel(&tmp);
}

void				print_amb(t_scene *s, char **to_print, int col, char *temp)
{
	char *tmp;

	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "ambiance { 0x");
	ft_strdel(&tmp);
	tmp = *to_print;
	print_col_mask(to_print, col, 0xff0000, 16);
	ft_strdel(&tmp);
	tmp = *to_print;
	print_col_mask(to_print, col, 0xff00, 8);
	ft_strdel(&tmp);
	tmp = *to_print;
	print_col_mask(to_print, col, 0xff, 0);
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " ; ");
	ft_strdel(&tmp);
	tmp = *to_print;
	temp = ft_putfloat(s->amb[1] * 100, 0);
	*to_print = ft_strjoin(*to_print, temp);
	ft_strdel(&tmp);
	ft_strdel(&temp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, " }\n");
	ft_strdel(&tmp);
}

void				print_text(t_scene *s, char **to_print, int col)
{
	char *tmp;

	(void)s;
	tmp = *to_print;
	if (col & EARTH)
		*to_print = ft_strjoin(*to_print, "texture { earth ");
	else if (col & FIRE)
		*to_print = ft_strjoin(*to_print, "texture { fire ");
	else if (col & BLACK)
		*to_print = ft_strjoin(*to_print, "texture { black ");
	else if (col & ICE)
		*to_print = ft_strjoin(*to_print, "texture { ice ");
	ft_strdel(&tmp);
}
