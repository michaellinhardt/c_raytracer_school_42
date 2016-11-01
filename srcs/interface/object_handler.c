/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 04:57:38 by tiboitel          #+#    #+#             */
/*   Updated: 2016/11/01 23:39:53 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raystruct.h>
#include <raytra_gen.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include "libft.h"

void	pscene_object_update_type(GtkWidget *pwidget,
	gpointer data)
{
	(void)pwidget;
	(void)data;
	int		type_name[10]  = {SPHERE, RECTANGLE, PLAN, CONE, CYLINDRE, COMPLEXE, TORUS,	BOLOID, TRIANGLE, ELLIPSE};
	int		i;
	t_gen	*raytracer;

	raytracer = (data) ? (t_gen *)data : NULL;
	i = 0;
	while (raytracer->to_move->type != type_name[i] && i < 10)
		i++;
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"SPHERE");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"RECTANGLE");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"PLAN");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"CONE");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"CYLINDRE");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"COMPLEXE");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"TORUS");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"BOLOID");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"TRIANGLE");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_type), NULL,
		"ELLIPSE");
	gtk_combo_box_set_active(GTK_COMBO_BOX(raytracer->pscene_object_type), i);
}

G_MODULE_EXPORT void	on_pscene_object_create_clicked(GtkWidget *pwidget,
		gpointer data)
{
	t_obj	*object;
	t_gen	*raytracer;
	t_obj	*tmp;
	char	*str;

	gtk_widget_set_sensitive(pwidget, FALSE);
	if (!(object = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return ;
	if (!(raytracer = (t_gen *)data))
		return ;
	object->name = ft_strdup(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_name)));
	/*
	 ** @Modification du nom pour eviter les doublons.
	 */
	tmp = raytracer->sc->obj;
	while (tmp != NULL)
	{
		if (!ft_strcmp(object->name, tmp->name))
		{
			str = ft_strjoin(object->name, "1");
			free(object->name);
			object->name = str;
			object->type = tmp->type;
			ft_memcpy(object->pos, tmp->pos, sizeof(tmp->pos));
			ft_memcpy(object->size, tmp->size, sizeof(tmp->size));	
			ft_memcpy(object->eff, tmp->eff, sizeof(tmp->eff));
			object->c_o = tmp->c_o;
			ft_memcpy(object->tri, tmp->tri, sizeof(t_vector));
			object->nor = tmp->nor;
			object->text = tmp->text;
			object->cut = NULL;
			object->comp = NULL;
			object->next = NULL; 
		}
		/*
		 ** Changer par un pushback.
		 */
		tmp = tmp->next;
	}
	object->next = raytracer->sc->obj;
	raytracer->sc->obj = object;
	on_pscene_current_scene_changed(raytracer->pscene_current_scene, raytracer);	
	gtk_widget_set_sensitive(pwidget, TRUE);
	// Creer un nouvel objet.
	// Verifier un objet a deja le meme non, si oui le modifier.
	// Verifier les proprietes?
	// Ajouter a la liste des objets.
	// Update de la liste deroulante de selection objet.
	(void)pwidget;
	(void)data;
	return ;
}

G_MODULE_EXPORT void	on_pscene_object_update_clicked(GtkWidget *pwidget,
		gpointer data)
{
	t_gen	*raytracer;
	
	gtk_widget_set_sensitive(pwidget, FALSE);
	if (!(raytracer = (t_gen *)data))
		return ;
	(void)pwidget;
	(void)data;
	pscene_object_update(raytracer);
	raytracing(raytracer);
	on_pscene_current_scene_changed(raytracer->pscene_object_select, raytracer);
	gtk_widget_set_sensitive(pwidget, TRUE);
	return ;
}

G_MODULE_EXPORT void	on_pscene_object_select_changed(GtkWidget *pwidget,
		gpointer data)
{
	t_gen	*raytracer;
	char	*objname;
	t_obj	*tmp;

	(void)pwidget;
	raytracer = NULL;
	if (!data)
		error(4, "unable to get pointer to raytracer\n");
	raytracer = (t_gen *)data;
	objname = gtk_combo_box_text_get_active_text(
		GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
	if (!objname)
		return ;
	tmp = raytracer->sc->obj;
	while (tmp)
	{
		if (!ft_strcmp(objname, tmp->name))
			raytracer->to_move = tmp;
		tmp = tmp->next;
	}
	pscene_object_hydrate(raytracer);
	free(objname);
}
