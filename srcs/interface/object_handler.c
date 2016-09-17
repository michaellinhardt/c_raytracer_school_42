/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 04:57:38 by tiboitel          #+#    #+#             */
/*   Updated: 2016/09/17 18:26:12 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include "libft.h"

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
