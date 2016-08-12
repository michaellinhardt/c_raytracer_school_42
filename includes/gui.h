/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 19:53:30 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/12 03:50:35 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H
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
void			on_pscene_current_scene_changed(GtkWidget *pwidget, gpointer data);
void			pscene_button_save(GtkWidget *pwdiget, gpointer data);
void			pscene_button_load(GtkWidget *pwdiget, gpointer data);
void			on_destroy_callback(GtkWidget *pwidget, gpointer *data);
void			on_pbutton_clicked(GtkWidget *pwidget, gpointer data);
#endif
