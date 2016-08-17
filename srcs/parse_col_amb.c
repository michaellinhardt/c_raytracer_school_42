/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_col_amb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 05:00:54 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/17 19:27:30 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		hexa_to_dec(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isalpha(c))
	{
		if (c >= 'a' && c <= 'f')
			return (10 + c - 'a');
		if (c >= 'A' && c <= 'F')
			return (10 + c - 'A');
	}
	error(3, "color");
	return (0);
}

static void		color_mid(char *tmp, char *line, int *color)
{
	int		i;
	int		j;

	i = ft_strlen(ft_strchr(tmp, '{')) - 1;
	j = ft_strlen(ft_strrchr(tmp, '}'));
	ft_strdel(&line);
	(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
	? error(2, "Malloc") : 1;
	ft_strdel(&tmp);
	tmp = ft_strtrim(line);
	ft_strdel(&line);
	if (!ft_strncmp(tmp, "0x", 2) && ft_strlen(tmp) == 8)
	{
		i = 8;
		*color = 0;
		while (--i != 1)
			*color = *color + hexa_to_dec(tmp[i]) * (pow(16, 7 - i));
		ft_strdel(&tmp);
	}
	else
		error(3, "color");
}

void			color_text(char *str, t_obj *o)
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

void			color(int fd, int *color, char c, t_obj *o)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && (tmp = ft_strtrim(line))
		&& !ft_strncmp(tmp, "color {", 7) && verif_str(tmp, 1))
		color_mid(tmp, line, color);
	else if (!ft_strncmp(tmp, "texture {", 9))
	{
		ft_strdel(&line);
		color_text(tmp, o);
		return ;
	}
	else
		error(3, "color");
	if (c)
	{
		if (get_next_line(fd, &line) > 0 && (tmp = ft_strtrim(line))
			&& !ft_strncmp(tmp, "}", 1))
		{
			ft_strdel(&line);
			ft_strdel(&tmp);
		}
		else
			error(3, "color");
	}
}

static void		ambiance_next(int *amb, char *temp, char *tmp)
{
	int i;

	if (verif_double(temp))
		amb[1] = ft_atob(temp);
	else
		error(3, "color");
	ft_strdel(&temp);
	if (!ft_strncmp(tmp, "0x", 2) && ft_strlen(tmp) == 8)
	{
		i = 8;
		amb[0] = 0;
		while (--i != 1)
			amb[0] = amb[0] + hexa_to_dec(tmp[i]) * (pow(16, 7 - i));
		ft_strdel(&tmp);
	}
	else
		error(3, "color");
	if (amb[1] < 0 || amb[1] > 100)
		error(3, "color");
}

void			ambiance(int *amb, char *line)
{
	char	**tab;
	char	*tmp;
	char	*temp;
	int		i;
	int		j;

	tab = NULL;
	temp = NULL;
	tmp = ft_strtrim(line);
	if (!verif_str(tmp, 1))
		error(3, "ambiance");
	i = ft_strlen(ft_strchr(tmp, '{')) - 1;
	j = ft_strlen(ft_strrchr(tmp, '}'));
	(!(temp = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
	? error(2, "Malloc") : 1;
	(!(tab = ft_strsplit(temp, ';'))) ? error(2, "Malloc") : 1;
	ft_strdel(&temp);
	ft_strdel(&tmp);
	tmp = ft_strtrim(tab[0]);
	temp = ft_strtrim(tab[1]);
	ft_strdel(&tab[0]);
	ft_strdel(&tab[1]);
	free(tab);
	tab = NULL;
	ambiance_next(amb, temp, tmp);
}
