/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 04:25:26 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/10 21:45:45 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		split_cam_mid(double *cam, char *temp, char c, int *i)
{
	char **pos;
	char *tmp;

	pos = ft_strsplit(temp, ';');
	while (pos[++*i])
	{
		tmp = ft_strtrim(pos[*i]);
		ft_strdel(&pos[*i]);
		if (verif_double(tmp))
			cam[*i + c] = ft_atob(tmp);
		else
			error(3, "camera");
		ft_strdel(&tmp);
	}
	free(pos);
	pos = NULL;
	if (*i != 3)
		error(3, "camera1");
}

static void		split_cam_first(double *cam, char *temp, char *tmp, char c)
{
	int		i;

	i = -1;
	if (ft_strchr_c(tmp, ';') == 2)
	{
		ft_strdel(&tmp);
		split_cam_mid(cam, temp, c, &i);
		ft_strdel(&temp);
	}
	else
		error(3, "camera");
}

static void		split_cam(double *cam, char **tab)
{
	char	*tmp;
	char	*temp;

	tmp = ft_strtrim(tab[0]);
	if (!ft_strncmp(tmp, "pos{", 4) && verif_str(tmp, 1))
	{
		temp = ft_strsub(tmp, 4, ft_strlen(tmp)
			- 4 - ft_strlen(ft_strchr(tmp, '}')));
		split_cam_first(cam, temp, tmp, 0);
		ft_strdel(&tab[0]);
	}
	else
		error(3, "camera");
	tmp = ft_strtrim(tab[1]);
	if (!ft_strncmp(tmp, "dir{", 4) && verif_str(tmp, 1))
	{
		temp = ft_strsub(tmp, 4, ft_strlen(tmp)
			- 4 - ft_strlen(ft_strchr(tmp, '}')));
		split_cam_first(cam, temp, tmp, 3);
		ft_strdel(&tab[1]);
	}
	else
		error(3, "camera");
	free(tab);
	tab = NULL;
}

static void		camera_mid(char *tmp, char *line, double *cam)
{
	char	**tab;
	int		i;
	int		j;

	if (!verif_str(tmp, 3))
		error(3, "camera");
	i = ft_strlen(ft_strchr(tmp, '{')) - 1;
	j = ft_strlen(ft_strrchr(tmp, '}'));
	ft_strdel(&line);
	(!(line = ft_strsub(tmp, ft_strlen(tmp) - i, i - j)))
	? error(2, "Malloc") : 1;
	ft_strdel(&tmp);
	(!(tab = ft_strsplit(line, ','))) ? error(2, "Malloc") : 1;
	ft_strdel(&line);
	split_cam(cam, tab);
}

void			camera(int fd, double *cam, char c)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (get_next_line(fd, &line) > 0 && (tmp = ft_strtrim(line))
		&& ((!ft_strncmp(tmp, "camera {", 8) && !c)
			|| (!ft_strncmp(tmp, "cut {", 5) && c)))
	{
		if (!ft_strncmp(tmp, "cut {", 5) && c && ft_strstr(tmp, "NULL"))
		{
			ft_bzero(cam, sizeof(double) * 6);
			return ;
		}
		camera_mid(tmp, line, cam);
	}
	else
		error(1, "camera");
}
