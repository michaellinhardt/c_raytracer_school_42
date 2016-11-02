/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_model.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:19:01 by tiboitel          #+#    #+#             */
/*   Updated: 2016/11/02 04:09:36 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <gdk/gdk.h>
#include <raytra_gen.h>
#include <raystruct.h>

void		pscene_spot_update(t_gen *raytracer)
{
	t_spot	*spot;

	if (!(spot = raytracer->selected_spot))
		return ;
	free(spot->name);
	spot->name = ft_strdup(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_name)));
	spot->pos[0] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_x)));
	spot->pos[1] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_y)));
	spot->pos[2] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_z)));
	spot->pos[3] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_dir_x)));
	spot->pos[4] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_dir_y)));
	spot->pos[5] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_dir_z)));
	spot->c_s = ft_atoi_base(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_spot_color)), "0123456789ABCDEF");
}

void		pscene_spot_hydrate(t_gen *raytracer)
{
	t_spot	*spot;
	char	*str;

	if (!(spot = raytracer->selected_spot))
		return ;
	set_text_entry_value(raytracer->pscene_spot_x, spot->pos[0]);
	set_text_entry_value(raytracer->pscene_spot_y, spot->pos[1]);
	set_text_entry_value(raytracer->pscene_spot_z, spot->pos[2]);
	set_text_entry_value(raytracer->pscene_spot_dir_x, spot->pos[3]);
	set_text_entry_value(raytracer->pscene_spot_dir_y, spot->pos[4]);
	set_text_entry_value(raytracer->pscene_spot_dir_z, spot->pos[5]);
	gtk_entry_set_text(GTK_ENTRY(raytracer->pscene_spot_name), spot->name);
	str = ft_itoa_base(spot->c_s, 16, 1);
	gtk_entry_set_text(GTK_ENTRY(raytracer->pscene_spot_color), str);
	free(str);
	str = NULL;
}
