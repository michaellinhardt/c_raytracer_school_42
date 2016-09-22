/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 02:10:37 by tiboitel          #+#    #+#             */
/*   Updated: 2016/09/22 15:22:04 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include "libft.h"
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

/*
 ** Change ces putains de fonctions de fichier lel.
 */ 

G_MODULE_EXPORT void	on_pwindow_destroy(GtkWidget *pwidget, gpointer data)
{
	(void)data;
	gtk_widget_destroy(pwidget);
	gtk_main_quit();
}

int		load_interface(t_gen *raytracer)
{
	GtkBuilder	*builder;
	GError		*err;
	GdkPixbuf 	*pixbuf;
	unsigned char *data;

	err = NULL;
	builder = NULL;	
	gtk_init(0, NULL);
	builder = gtk_builder_new();
	if (builder == NULL)
		return (0);
	gtk_builder_add_from_file(builder, "resources/interface.glade", &err);
	if (err != NULL)
	{
		g_error("%s", err->message);
		g_error_free(err);
		return (0);
	}
	CH_GET_WIDGET(builder, pwindow, raytracer);
	CH_GET_WIDGET(builder, pdrawarea, raytracer);
	CH_GET_WIDGET(builder, pscene_choosefile, raytracer);
	CH_GET_WIDGET(builder, pscene_current_scene, raytracer);
	CH_GET_WIDGET(builder, pscene_object_select, raytracer);
	CH_GET_WIDGET(builder, pscene_object_type, raytracer);
	CH_GET_WIDGET(builder, pscene_object_create, raytracer);
	CH_GET_WIDGET(builder, pscene_object_update, raytracer);
	CH_GET_WIDGET(builder, pscene_object_x, raytracer);
	CH_GET_WIDGET(builder, pscene_object_y, raytracer);
	CH_GET_WIDGET(builder, pscene_object_z, raytracer);
	CH_GET_WIDGET(builder, pscene_object_dir_x, raytracer);
	CH_GET_WIDGET(builder, pscene_object_dir_y, raytracer);
	CH_GET_WIDGET(builder, pscene_object_dir_z, raytracer);
	CH_GET_WIDGET(builder, pscene_object_size_x, raytracer);
	CH_GET_WIDGET(builder, pscene_object_size_y, raytracer);
	CH_GET_WIDGET(builder, pscene_object_size_z, raytracer);
	CH_GET_WIDGET(builder, pscene_object_color, raytracer);
	CH_GET_WIDGET(builder, pscene_object_color, raytracer);
	CH_GET_WIDGET(builder, pscene_object_name, raytracer);
	CH_GET_WIDGET(builder, pscene_object_negative, raytracer);
	CH_GET_WIDGET(builder, pscene_object_transparence, raytracer);
	CH_GET_WIDGET(builder, pscene_object_reflexion, raytracer);
	CH_GET_WIDGET(builder, pscene_object_refraction, raytracer);
	if (!(data = ft_memalloc(1680 * 24 * 1050)))
		return (0);
	pixbuf = gtk_new_image(data, 1680, 1050);
	gtk_put_image_to_window(GTK_IMAGE(raytracer->pdrawarea), pixbuf);
	gtk_builder_connect_signals(builder, raytracer);		
	free(data);
	(void)pixbuf;
	(void)data;
	(void)raytracer;
	g_clear_object(&builder);
	return (1);
}
