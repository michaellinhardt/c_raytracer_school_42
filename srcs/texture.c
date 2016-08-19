/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 10:21:27 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/19 01:07:37 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

int		texture_earth(double u, double v, char *str, void *mlx)
{
	static t_tex	s;
	int				px;
	void			*test;
	t_obj			*tmp;

	if (str)
	{
		test = mlx_xpm_file_to_image(mlx, "./resources/earth.xpm",
			&s.heigh, &s.weigh);
		s.data = mlx_get_data_addr(test, &s.y_line, &s.x_line, &px);
		free(test);
	}
	else
	{
		u = (int)(u * s.heigh);
		if (u < 0)
			u = 0;
		v = (int)(v * s.weigh);
		tmp = (t_obj *)mlx;
		px = (int)(u * s.y_line) + (int)(v * s.x_line);
		return ((int)((s.data[px + 2] << 16) + (s.data[px + 1] << 8)
			+ (s.data[px])));
	}
	return (1);
}

int		texture_black(double u, double v, char *str, void *mlx)
{
	static t_tex	s;
	int				px;
	void			*test;
	t_obj			*tmp;

	if (str)
	{
		test = mlx_xpm_file_to_image(mlx, "./resources/black.xpm",
			&s.heigh, &s.weigh);
		s.data = mlx_get_data_addr(test, &s.y_line, &s.x_line, &px);
		free(test);
	}
	else
	{
		u = (int)(u * s.heigh);
		if (u < 0)
			u = 0;
		v = (int)(v * s.weigh);
		tmp = (t_obj *)mlx;
		px = (int)(u * s.y_line) + (int)(v * s.x_line);
		return ((int)((s.data[px + 2] << 16) + (s.data[px + 1] << 8)
			+ (s.data[px])));
	}
	return (1);
}

int		texture_fire(double u, double v, char *str, void *mlx)
{
	static t_tex	s;
	int				px;
	void			*test;
	t_obj			*tmp;

	if (str)
	{
		test = mlx_xpm_file_to_image(mlx, "./resources/fire.xpm",
			&s.heigh, &s.weigh);
		s.data = mlx_get_data_addr(test, &s.y_line, &s.x_line, &px);
		free(test);
	}
	else
	{
		u = (int)(u * s.heigh);
		if (u < 0)
			u = 0;
		v = (int)(v * s.weigh);
		tmp = (t_obj *)mlx;
		px = (int)(u * s.y_line) + (int)(v * s.x_line);
		return ((int)((s.data[px + 2] << 16) + (s.data[px + 1] << 8)
			+ (s.data[px])));
	}
	return (1);
}

int		texture_ice(double u, double v, char *str, void *mlx)
{
	static t_tex	s;
	int				px;
	void			*test;
	t_obj			*tmp;

	if (str)
	{
		test = mlx_xpm_file_to_image(mlx, "./resources/glace.xpm",
			&s.heigh, &s.weigh);
		s.data = mlx_get_data_addr(test, &s.y_line, &s.x_line, &px);
		free(test);
	}
	else
	{
		u = (int)(u * s.heigh);
		if (u < 0)
			u = 0;
		v = (int)(v * s.weigh);
		tmp = (t_obj *)mlx;
		px = (int)(u * s.y_line) + (int)(v * s.x_line);
		return ((int)((s.data[px + 2] << 16) + (s.data[px + 1] << 8)
			+ (s.data[px])));
	}
	return (1);
}
