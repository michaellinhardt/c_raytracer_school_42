/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 02:10:37 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/12 06:33:29 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include "libft.h"
#include <raystruct.h>
#include <raytra_gen.h>

G_MODULE_EXPORT void	pscene_button_save_clicked(GtkWidget *pwidget, gpointer data)
{
	(void)pwidget;
	(void)data;
}

G_MODULE_EXPORT void	on_pscene_object_select_changed(GtkWidget *pwidget, gpointer data)
{
	t_gen	*raytracer;
	char	*objname;
	t_obj	*tmp;

	(void)pwidget;
	raytracer = NULL;
	if (!data)
	{
		error(4, "unable to get pointer to raytracer\n");
	}
	raytracer = (t_gen *)data;
	objname = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
	if (!objname)
		return ;
	tmp = raytracer->sc->obj;
	while (tmp)
	{
		if (!ft_strcmp(objname, tmp->name))
			raytracer->to_move = tmp;
		tmp = tmp->next;
	}
}

G_MODULE_EXPORT void	on_pscene_current_scene_changed(GtkWidget *pwidget, gpointer data)
{
	t_scene		*head;
	t_scene		*tmp;
	char		*current;
	t_gen		*raytracer;

	tmp = NULL;
	current = NULL;
	raytracer = NULL;
	if (data == NULL)
	{
		error(4, "Unable to get pointer to raytracer\n");
		return ;
	}
	raytracer = (t_gen *)data;
	head = raytracer->sc;
	tmp = raytracer->sc;
	current = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(
				raytracer->pscene_current_scene));
	if (!current)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, current) == 0)
		{
			raytracer->sc = tmp;
			raytracer->to_move = NULL;
			t_obj	*otmp;

			gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
			otmp = raytracer->sc->obj;
			/* Redondance de code avec button_load, isoler les acteurs */
			while (otmp)
			{
				gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select),
						NULL, otmp->name);
				otmp = otmp->next;
			}
			/* Fin de la redondance */
			raytracing(raytracer);
		}
		tmp = tmp->next;
	}
	raytracer->sc = head;
	(void)pwidget;
	(void)data;
}

G_MODULE_EXPORT void	pscene_button_load_clicked(GtkWidget *pwidget, gpointer data)
{
	t_gen			*raytracer;
	char			*filename;
	GtkFileChooser	*chooser;
	t_scene			*tmp;	
	t_obj	*otmp;

	(void)pwidget;
	if (!data)
	{
		error(4, "Unable to get pointer to raytracer\n");
		return ;
	}
	raytracer = NULL;
	filename = NULL;
	chooser = NULL;
	tmp = NULL;
	raytracer = (t_gen *)data;
	raytracer->to_move = NULL;
	chooser = GTK_FILE_CHOOSER(raytracer->pscene_choosefile);
	filename = gtk_file_chooser_get_filename(chooser);
	parse_scene(raytracer, filename);
	/*
	 ** @Ajout des elements au combo box.
	 */	
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_current_scene));
	tmp = raytracer->sc;
	while (tmp)
	{
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_current_scene),
				NULL, tmp->name);
		tmp = tmp->next;
	}
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
	otmp = raytracer->sc->obj;
	while (otmp)
	{
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select),
				NULL, otmp->name);
		otmp = otmp->next;
	}
	/*
	 ** @Lancement de l'affichage.
	 */
	raytracing(raytracer);
	g_free(filename);
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
	CH_GET_WIDGET(builder, pscene_choosefile, raytracer);
	CH_GET_WIDGET(builder, pscene_current_scene, raytracer);
	CH_GET_WIDGET(builder, pscene_object_select, raytracer);
	if (!(data = ft_memalloc(1680 * 24 * 1050)))
		return (0);
	pixbuf = gtk_new_image(data, 1680, 1050);
	gtk_put_image_to_window(GTK_IMAGE(raytracer->pdrawarea), pixbuf);
	gtk_builder_connect_signals(builder, raytracer);		
	g_object_unref(pixbuf);
	g_object_unref(builder);
	free(data);
	return (1);
}
