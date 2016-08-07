/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 02:10:37 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/07 05:05:05 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <h_gui.h>
#include "libft.h"
#include <h_raystruct.h>
#include <h_raytra_gen.h>

G_MODULE_EXPORT void	on_pbutton_clicked(GtkWidget *pwidget, gpointer data)
{
	(void)pwidget;
	(void)data;
	ft_putendl("DU TURFU");
}

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
	
	if (!(data = malloc(1680 * 24 * 1050)))
		return (0);
	ft_bzero(data, sizeof(data));	
	pixbuf = gtk_new_image(data, 1680, 1050);
	gtk_put_image_to_window(GTK_IMAGE(raytracer->pdrawarea), pixbuf);
	gtk_builder_connect_signals(builder, raytracer);
	gtk_widget_show_all(raytracer->pwindow);
	gtk_main();
	g_object_unref(pixbuf);
	g_object_unref(builder);
	free(data);
	return (1);
}
