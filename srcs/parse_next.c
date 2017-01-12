/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 02:30:01 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/01/03 15:02:15 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		return_type_spot(char **tmp)
{
	if (ft_strequ(*tmp, "directional"))
	{
		ft_strdel(tmp);
		return (DIIR);
	}
	else if (ft_strequ(*tmp, "point"))
	{
		ft_strdel(tmp);
		return (POINT);
	}
	else
		error(3, "type spot1");
	return (0);
}

int				type_spot(int fd)
{
	char	*tmp;
	char	*line;
	int		i;
	int		j;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && ft_strstr(line, "type {")
		&& verif_str(line, 1))
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		i = ft_strlen(ft_strchr(tmp, '{')) - 1;
		j = ft_strlen(ft_strrchr(tmp, '}'));
		if (!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
			error(2, "Malloc");
		ft_strdel(&tmp);
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		return (return_type_spot(&tmp));
	}
	else
		error(1, "type spot");
	return (0);
}

static int		return_type(char **tmp)
{
	int type;

	type = 0;
	if (ft_strequ(*tmp, "sphere"))
		type = SPHERE;
	else if (ft_strequ(*tmp, "rectangle"))
		type = RECTANGLE;
	else if (ft_strequ(*tmp, "plan"))
		type = PLAN;
	else if (ft_strequ(*tmp, "cone"))
		type = CONE;
	else if (ft_strequ(*tmp, "cylindre"))
		type = CYLINDRE;
	else if (ft_strequ(*tmp, "para"))
		type = BOLOID;
	else if (ft_strequ(*tmp, "triangle"))
		type = TRIANGLE;
	else if (ft_strequ(*tmp, "ellipse"))
		type = ELLIPSE;
	else
		error(3, "type object");
	ft_strdel(tmp);
	return (type);
}

int				type(int fd)
{
	char	*tmp;
	char	*line;
	int		i;
	int		j;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && ft_strstr(line, "type {")
		&& verif_str(line, 1))
	{
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		i = ft_strlen(ft_strchr(tmp, '{')) - 1;
		j = ft_strlen(ft_strrchr(tmp, '}'));
		if (!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
			error(2, "Malloc");
		ft_strdel(&tmp);
		tmp = ft_strtrim(line);
		ft_strdel(&line);
		return (return_type(&tmp));
	}
	else
		error(1, "type object");
	return (0);
}
