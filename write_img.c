/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 07:58:30 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/25 07:42:41 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

static void	write_header(int fd)
{
	int						filesize;
	static unsigned char	header[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0,
	54, 0, 0, 0};
	static unsigned char	infoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 32, 0};

	filesize = 54 + 4 * W_X * W_Y;
	header[2] = (unsigned char)(filesize);
	header[3] = (unsigned char)(filesize >> 8);
	header[4] = (unsigned char)(filesize >> 16);
	header[5] = (unsigned char)(filesize >> 24);
	infoheader[4] = (unsigned char)(W_X);
	infoheader[5] = (unsigned char)(W_X >> 8);
	infoheader[6] = (unsigned char)(W_X >> 16);
	infoheader[7] = (unsigned char)(W_X >> 24);
	infoheader[8] = (unsigned char)(W_Y);
	infoheader[9] = (unsigned char)(W_Y >> 8);
	infoheader[10] = (unsigned char)(W_Y >> 16);
	infoheader[11] = (unsigned char)(W_Y >> 24);
	write(fd, header, 14);
	write(fd, infoheader, 40);
}

static void	fill_img(int fd, char *str, t_id t)
{
	int		i;
	char	s[t.s_line * W_Y + 1];
	char	tmp[t.s_line + 1];

	ft_memcpy(s, str, t.s_line * W_Y);
	i = 0;
	while (i < W_Y / 2)
	{
		ft_memcpy(tmp, s + i * t.s_line, t.s_line);
		ft_memcpy(s + i * t.s_line, s + (W_Y - i - 1) * t.s_line, t.s_line);
		ft_memcpy(s + (W_Y - i - 1) * t.s_line, tmp, t.s_line);
		++i;
	}
	write(fd, s, t.s_line * W_Y);
}

static char	*name_file(t_gen *s, int *nb)
{
	char *tmp;
	char *temp;

	tmp = ft_itoa(nb[(int)s->sc->nb]);
	nb[(int)s->sc->nb]++;
	while (ft_strlen(tmp) < 3)
	{
		temp = tmp;
		tmp = ft_strjoin("0", tmp);
		ft_strdel(&temp);
	}
	temp = tmp;
	tmp = ft_strjoin(s->sc->name, tmp);
	ft_strdel(&temp);
	temp = tmp;
	tmp = ft_strjoin("./image/", tmp);
	ft_strdel(&temp);
	temp = tmp;
	tmp = ft_strjoin(tmp, ".bmp");
	ft_strdel(&temp);
	return (tmp);
}

void		print_bmp(char *str, t_id t, t_gen *s)
{
	int			fd;
	static int	nb[20] = {0};
	static char c = 0;
	char		*name;

	if (access("image", R_OK | W_OK) < 0)
		system("make img");
	name = name_file(s, nb);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0755);
	ft_strdel(&name);
	write_header(fd);
	fill_img(fd, str, t);
	close(fd);
	c = 1;
}
