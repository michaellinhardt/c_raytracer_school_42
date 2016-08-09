/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_gui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 19:53:30 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/09 22:10:17 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GUI_H
# define FT_GUI_H
#include <glib.h>
#include <gtk/gtk.h>

typedef struct	s_gen t_gen;

#define CH_GET_OBJECT(builder, name, type, data) \
	data->name = type(gtk_builder_get_object(builder, #name) )
#define CH_GET_WIDGET(builder, name, data) \
	CH_GET_OBJECT(builder, name, GTK_WIDGET, data )

int				load_interface(t_gen *raycaster);
GdkPixbuf		*gtk_new_image(unsigned char *data, int width, int heigth);
void			gtk_put_pixel(GdkPixbuf *pixbuf, int x, int y, int color);
int				gtk_put_image_to_window(GtkImage *image, GdkPixbuf *pixbuf);

/*
 ** @Callback section.
 */
void			on_destroy_callback(GtkWidget *pwidget, gpointer *data);
void			on_pbutton_clicked(GtkWidget *pwidget, gpointer data);
#endif
