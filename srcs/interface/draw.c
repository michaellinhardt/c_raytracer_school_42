/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 04:11:05 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/17 22:32:21 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytra_gen.h>

GdkPixbuf	*gtk_new_image(unsigned char *data, int width, int height)
{
	GdkPixbuf	*pixbuf;
	GBytes		*buffer;
	
	buffer = NULL;
	pixbuf = NULL;
	buffer = g_bytes_new(data, width * height * 3);
	if (!(pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, 0, 8, width, height, 3 * width)))
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

void	gtk_put_pixel(GdkPixbuf *pixbuf, int x, int y, int color)
{
	int				width;
	int				height;
	int				rowstride;
	int				n_channels;
	unsigned char	*buffer;
	unsigned char	*p;

	n_channels = gdk_pixbuf_get_n_channels(pixbuf);
	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);
	rowstride = gdk_pixbuf_get_rowstride(pixbuf);
	buffer = gdk_pixbuf_get_pixels(pixbuf);
	p = buffer + y * rowstride + x * n_channels;
	p[0] = (color & 0xFF0000) >> 16;
	p[1] = (color & 0x00FF00) >> 8;
	p[2] = (color & 0xFF);
}

int		gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf)
{
	gtk_image_clear(image);
	gtk_image_set_from_pixbuf(image, pixbuf);
	return (1);
}
