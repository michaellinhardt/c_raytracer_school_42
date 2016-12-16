/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 20:13:01 by tiboitel          #+#    #+#             */
/*   Updated: 2016/12/16 19:32:01 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

G_MODULE_EXPORT void	on_pfilter_button_save_clicked(GtkWidget *pwidget,
		gpointer data)
{
	t_gen	*raytracer;

	(void)pwidget;
	if (!(raytracer = (t_gen *)data))
		return ;
	/* Add function write_img here. Don't know here work. */
}

G_MODULE_EXPORT void	on_pfilter_button_apply_clicked(GtkWidget *pwidget,
		gpointer data)
{
	int		filter_id;
	t_gen	*raytracer;

	if (!(raytracer = (t_gen *)data))
		return ;
	if ((filter_id = gtk_combo_box_get_active(
		GTK_COMBO_BOX(raytracer->pfilter_choose_filter))) == -1)
		return ;
	/*
	 ** Apply selected filter.
	 */
	(void)pwidget;
	(void)data;
}
