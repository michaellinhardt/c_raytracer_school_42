/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene_spot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 07:15:29 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 07:18:32 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"

static void			print_cam_end(int i, char **tp, double *cam)
{
	char	*tmp;
	char	*temp;

	while (i < 6)
	{
		tmp = *tp;
		temp = ft_putfloat(cam[i], 0);
		*tp = ft_strjoin(*tp, temp);
		ft_strdel(&tmp);
		ft_strdel(&temp);
		tmp = *tp;
		if (i != 5)
			*tp = ft_strjoin(*tp, ";");
		else
		{
			*tp = ft_strjoin(*tp, "}}\n");
			ft_strdel(&tmp);
			break ;
		}
		ft_strdel(&tmp);
		++i;
	}
}

void				print_cam(t_scene *s, char **tp, double *cam, char c)
{
	char	*tmp;
	char	*temp;
	int		i;

	(void)s;
	tmp = *tp;
	*tp = (!c) ? ft_strjoin(*tp, "camera {pos{") : ft_strjoin(*tp, "cut {pos{");
	ft_strdel(&tmp);
	i = -1;
	while (++i < 3)
	{
		tmp = *tp;
		temp = ft_putfloat(cam[i], 0);
		*tp = ft_strjoin(*tp, temp);
		ft_strdel(&tmp);
		ft_strdel(&temp);
		tmp = *tp;
		*tp = (i != 2) ? ft_strjoin(*tp, ";") : ft_strjoin(*tp, "}, dir{");
		ft_strdel(&tmp);
	}
	print_cam_end(i, tp, cam);
	ft_strdel(&tmp);
	ft_strdel(&temp);
}

static void			print_spot_type(t_scene *s, char **to_print, char type)
{
	char *tmp;

	tmp = *to_print;
	(void)s;
	if (type & DIR)
		*to_print = ft_strjoin(*to_print, "type {directional}\n");
	if (type & POINT)
		*to_print = ft_strjoin(*to_print, "type {point}\n");
	ft_strdel(&tmp);
}

static void			print_spot_name(t_scene *s, char **to_print, char *name)
{
	char *tmp;

	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "name {");
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, name);
	ft_strdel(&tmp);
	tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "}\n");
	ft_strdel(&tmp);
	(void)s;
}

void				print_spot(t_scene *s, char **to_print, char **tmp)
{
	t_spot	*spot;

	print_cam(s, to_print, s->cam, 0);
	spot = s->spot;
	while (spot)
	{
		*tmp = *to_print;
		*to_print = ft_strjoin(*to_print, "spot {\n");
		ft_strdel(tmp);
		print_spot_name(s, to_print, spot->name);
		print_spot_type(s, to_print, spot->type);
		print_cam(s, to_print, spot->pos, 0);
		print_col(to_print, spot->c_s, NULL);
		*tmp = *to_print;
		*to_print = ft_strjoin(*to_print, "}\n");
		ft_strdel(tmp);
		spot = spot->next;
	}
	print_amb(s, to_print, s->amb[0], NULL);
	*tmp = *to_print;
	*to_print = ft_strjoin(*to_print, "objects {\n");
	ft_strdel(tmp);
}
