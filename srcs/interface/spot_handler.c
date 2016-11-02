/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 00:42:05 by tiboitel          #+#    #+#             */
/*   Updated: 2016/11/02 04:08:09 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include "libft.h"

void	pscene_spot_select_update(t_gen *raytracer)
{
	if (!raytracer)
		return ;
	pscene_spot_update(raytracer);
	raytracing(raytracer);
}

G_MODULE_EXPORT void	on_pscene_spot_select_changed(GtkWidget *pwidget,
		gpointer data)
{
	char		*scene_name;
	char		*spot_name;
	t_spot		*spots;
	t_spot		*tmp;
	t_scene		*current_scene;
	t_gen		*raytracer;

	(void)pwidget;
	(void)data;	
	if (!(raytracer = (t_gen *)(data)))
		return ;
	if (!(spot_name = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(raytracer->pscene_spot_select))))
		return ;
	if (!(scene_name = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(raytracer->pscene_current_scene))))
		return ;
	current_scene = raytracer->sc;
	while (current_scene)
	{
		if (!ft_strcmp(scene_name, current_scene->name))
			spots = current_scene->spot;
		current_scene = current_scene->next;
	}
	tmp = spots;
	while (tmp)
	{
		if (!ft_strcmp(spot_name, tmp->name))
			raytracer->selected_spot = tmp;
		tmp = tmp->next;
	}
	pscene_spot_hydrate(raytracer);
}

G_MODULE_EXPORT	void	on_pscene_spot_update_button_clicked(GtkWidget *pwidget,
	gpointer data)
{
	(void)pwidget;
	(void)data;
	t_gen	*raytracer;
	
	raytracer = NULL;
	raytracer = (t_gen *)data;
	if (!raytracer)
		return ;
	pscene_spot_update(raytracer);
	raytracing(raytracer);

}
