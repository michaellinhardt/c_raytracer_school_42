/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 04:11:05 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/07 04:51:49 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <h_raytra_gen.h>

GdkPixbuf	*gtk_new_image(unsigned char *data, int width, int height)
{
	GdkPixbuf	*pixbuf;

	pixbuf = NULL;
	if (!(pixbuf = gdk_pixbuf_new_from_bytes(g_bytes_new(data, width * height * 24), GDK_COLORSPACE_RGB, 0, 8, width,
		height, 8 * width)))
		return (NULL);
	return (pixbuf);
}

int		gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf)
{
	gtk_image_set_from_pixbuf(image, pixbuf);
	return (1);
}
