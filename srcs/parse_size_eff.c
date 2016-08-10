/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size_eff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 06:18:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/10 21:46:15 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		size_mid(double *size, char **temp, char *tmp)
{
	int		i;

	i = -1;
	while (temp[++i])
	{
		tmp = ft_strtrim(temp[i]);
		if (tmp && verif_double(tmp))
			size[i] = ft_atob(tmp);
		else
			error(3, "size object");
		ft_strdel(&tmp);
		ft_strdel(&temp[i]);
	}
	free(temp);
	temp = NULL;
	if (i != 3)
		error(3, "size object");
}

void			size(int fd, double *size)
{
	char	*line;
	char	*tmp;
	char	**temp;
	int		i;
	int		j;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && ft_strstr(line, "size {")
		&& verif_str(line, 1))
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		i = ft_strlen(ft_strchr(tmp, '{')) - 1;
		j = ft_strlen(ft_strrchr(tmp, '}'));
		(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
		? error(2, "Malloc") : 1;
		ft_strdel(&tmp);
		(!(temp = ft_strsplit(line, ';'))) ? error(2, "Malloc") : 1;
		ft_strdel(&line);
		size_mid(size, temp, tmp);
	}
	else
		error(1, "size object");
}

static void		effect_mid(double *eff, char **temp, char *tmp)
{
	int		i;

	i = -1;
	while (temp[++i])
	{
		tmp = ft_strtrim(temp[i]);
		if (tmp && verif_double(tmp))
			eff[i] = ft_atob(tmp);
		else
			error(3, "effect object");
		ft_strdel(&tmp);
		ft_strdel(&temp[i]);
	}
	free(temp);
	temp = NULL;
	if (i != 4 || eff[0] < 0 || eff[1] < 0 || eff[2] < 0
		|| eff[0] > 100 || eff[1] > 100 || eff[2] > 100
		|| (eff[3] != 0 && eff[3] != 1))
		error(3, "effect object");
}

void			effect(int fd, double *eff)
{
	char	*line;
	char	*tmp;
	char	**temp;
	int		i;
	int		j;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && ft_strstr(line, "effect {")
		&& verif_str(line, 1))
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		i = ft_strlen(ft_strchr(tmp, '{')) - 1;
		j = ft_strlen(ft_strrchr(tmp, '}'));
		(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
		? error(2, "Malloc") : 1;
		ft_strdel(&tmp);
		(!(temp = ft_strsplit(line, ';'))) ? error(2, "Malloc") : 1;
		ft_strdel(&line);
		effect_mid(eff, temp, tmp);
	}
	else
		error(1, "effect object");
}
