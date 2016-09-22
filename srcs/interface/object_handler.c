/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 04:57:38 by tiboitel          #+#    #+#             */
/*   Updated: 2016/09/22 17:55:29 by tiboitel         ###   ########.fr       */
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
	(void)pwidget;
	(void)data;
	return ;
}

G_MODULE_EXPORT void	on_pscene_object_update_clicked(GtkWidget *pwidget,
		gpointer data)
{
	(void)pwidget;
	(void)data;
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
