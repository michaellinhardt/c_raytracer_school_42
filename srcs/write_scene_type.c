/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 07:23:20 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 07:24:01 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"

void			print_type(t_scene *s, char **to_print, char type)
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
	if (type & BOLOID)
		*to_print = ft_strjoin(*to_print, "para }\n");
	if (type & TRIANGLE)
		*to_print = ft_strjoin(*to_print, "triangle }\n");
	if (type & ELLIPSE)
		*to_print = ft_strjoin(*to_print, "ellipse }\n");
	ft_strdel(&tmp);
}

void			print_size_eff(t_scene *s, char **tp, double *size, char c)
{
	char	*tmp;
	char	*temp;
	int		i;

	(void)s;
	tmp = *tp;
	*tp = (!c) ? ft_strjoin(*tp, "size {") : ft_strjoin(*tp, "effect {");
	ft_strdel(&tmp);
	i = 0;
	while (i < 3 + c)
	{
		tmp = *tp;
		temp = ft_putfloat(size[i], 0);
		*tp = ft_strjoin(*tp, temp);
		ft_strdel(&tmp);
		ft_strdel(&temp);
		tmp = *tp;
		if (i != 3 + c - 1)
			*tp = ft_strjoin(*tp, ";");
		else
			*tp = ft_strjoin(*tp, "}\n");
		ft_strdel(&tmp);
		++i;
	}
}
