/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 02:15:07 by tiboitel          #+#    #+#             */
/*   Updated: 2016/11/02 03:49:44 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include "libft.h"

G_MODULE_EXPORT void	pscene_button_save_clicked(GtkWidget *pwidget, gpointer data)
{
	t_scene		*head;
	t_scene		*tmp;
	char		*current;

	(void)pwidget;
	head = ((t_gen *)(data))->sc;
	if (!head)
		return ;
	tmp = head;
	current = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(
				((t_gen *)(data))->pscene_current_scene));
	if (!current)
		return ;
	while (tmp)
	{
		if (!ft_strcmp(current, tmp->name))
		{
			print_scene(tmp);
			free(current);
			return ;
		}
		tmp = tmp->next;
	}
	free(current);
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
	if (!(raytracer = (t_gen *)data))
		return ;
	head = raytracer->sc;
	tmp = raytracer->sc;
	current = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(
				raytracer->pscene_current_scene));
	if (!current)
		return ;
	while (tmp)
	{
		/* Chargement des objets dans la liste deroulante */
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
		}
		tmp = tmp->next;
	}
	free(current);
	gtk_combo_box_set_active(GTK_COMBO_BOX(raytracer->pscene_object_select), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(raytracer->pscene_current_scene), 0);
	raytracing(raytracer);
	raytracer->sc = head;
	(void)pwidget;
}

G_MODULE_EXPORT void	pscene_button_load_clicked(GtkWidget *pwidget, gpointer data)
{
	t_gen			*raytracer;
	char			*filename;
	GtkFileChooser	*chooser;
	t_scene			*tmp;	
	t_obj			*otmp;
	t_spot			*stmp;

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
	(void)chooser;
	(void)filename;
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
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_spot_select));
	stmp = raytracer->sc->spot;
	while (stmp)
	{
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_spot_select), NULL, stmp->name);
		stmp = stmp->next;
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(raytracer->pscene_current_scene), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(raytracer->pscene_object_select), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(raytracer->pscene_spot_select), 0);
	g_free(filename);
	raytracing(raytracer);
}
