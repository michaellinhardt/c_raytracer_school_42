/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:22 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:22 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void	pixel_to_char(t_gen *s, int color, int x, int y)
{
	int		*ptr;

	ptr = (int *)s->data;
	ptr[W_X * y + x] = color;
}

void	*mlx_new_img(t_mlx *m, t_img *img, int width, int heigh)
{
	img->width = width;
	img->heigh = heigh;
	if (!(img->img)
	&& !(img->img = mlx_new_image(m->mlx, img->width, img->heigh)))
		error(2, "mlx_new_image()");
	if (!(img->str))
	{
		if (!(img->str = mlx_get_data_addr(img->img
			, &img->bpp, &img->sl, &img->end)))
			error(2, "mlx_get_data_addr()");
		img->ptr = (int *)img->str;
	}
	return (img->img);
}

void	*mlx_xpmtostruct(t_mlx *m, t_img *img, char *file)
{
	if (!(img->img)
	&& !(img->img = mlx_xpm_file_to_image(m->mlx, file
												, &img->width, &img->heigh)))
		error(2, "mlx_xpm_file_to_image()");
	if (!(img->str))
	{
		if (!(img->str = mlx_get_data_addr(img->img
			, &img->bpp, &img->sl, &img->end)))
			error(2, "mlx_get_data_addr()");
		img->ptr = (int *)img->str;
	}
	return (img->img);
}

int		itow(t_mlx *m, void *img, int x, int y)
{
	if (!mlx_put_image_to_window(m->mlx, m->win, img, x, y))
		error(2, "mlx_put_image_to_window()");
	return (1);
}
