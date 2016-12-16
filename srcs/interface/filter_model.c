/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 19:07:30 by tiboitel          #+#    #+#             */
/*   Updated: 2016/12/16 19:20:06 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	pfilter_model_hydrate(t_gen *raytracer)
{
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter));
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Abstract");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Antialiasing");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Luminosite");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Obscurcir");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Negatif");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Sepia");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Technicolor");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Polaroid");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "BGR");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Kodachrome");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Browni");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Vintage");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "Noir et blanc");
	gtk_combo_box_text_append(
		GTK_COMBO_BOX_TEXT(raytracer->pfilter_choose_filter), NULL, "LSD");
	gtk_combo_box_set_active(
		GTK_COMBO_BOX(raytracer->pfilter_choose_filter), 0);
}
