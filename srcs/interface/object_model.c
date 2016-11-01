/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 17:52:47 by tiboitel          #+#    #+#             */
/*   Updated: 2016/11/01 23:50:32 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raytra_gen.h>
#include <raystruct.h>
#include "libft.h"

void		pscene_object_hydrate(t_gen *raytracer)
{
	char	*str;

	if (raytracer->to_move == NULL)
		return ;
	set_text_entry_value(raytracer->pscene_object_x,
		raytracer->to_move->pos[0]);
	set_text_entry_value(raytracer->pscene_object_y,
		raytracer->to_move->pos[1]);
	set_text_entry_value(raytracer->pscene_object_z,
		raytracer->to_move->pos[2]);
	set_text_entry_value(raytracer->pscene_object_dir_x,
		raytracer->to_move->pos[3]);
	set_text_entry_value(raytracer->pscene_object_dir_y,
		raytracer->to_move->pos[4]);
	set_text_entry_value(raytracer->pscene_object_dir_z,
		raytracer->to_move->pos[5]);
	set_text_entry_value(raytracer->pscene_object_size_x,
		raytracer->to_move->size[0]);
	set_text_entry_value(raytracer->pscene_object_size_y,
		raytracer->to_move->size[1]);
	set_text_entry_value(raytracer->pscene_object_size_z,
		raytracer->to_move->size[2]);
	str = NULL;
	str = ft_itoa_base(raytracer->to_move->c_o, 16, 1);
	gtk_entry_set_text(GTK_ENTRY(raytracer->pscene_object_color), str);
	free(str);
	str = NULL;
	gtk_entry_set_text(GTK_ENTRY(raytracer->pscene_object_name),
		raytracer->to_move->name);
	set_text_entry_value(raytracer->pscene_object_negative,
		raytracer->to_move->eff[3]);
	set_text_entry_value(raytracer->pscene_object_transparence,
		raytracer->to_move->eff[0]);
	set_text_entry_value(raytracer->pscene_object_reflexion,
		raytracer->to_move->eff[1]);
	set_text_entry_value(raytracer->pscene_object_refraction,
		raytracer->to_move->eff[2]);
	// Ajouter menu deroulants type de l'objet.
	pscene_object_update_type(raytracer->pscene_object_type, raytracer);
	(void)raytracer;
}

void		pscene_object_update(t_gen *raytracer)
{
	/*
	 * Si le nom de l'objet a change mettre a jour le menu deroulant de selection des objets.
	 */
	t_obj	*object;

	object = raytracer->to_move;
	if (object == NULL)
		return ;
	free(object->name);
	object->name = ft_strdup(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_name)));
	object->pos[0] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_x)));
	object->pos[1] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_y)));
	object->pos[2] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_z)));
	object->pos[3] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_dir_x)));
	object->pos[4] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_dir_y)));
	object->pos[5] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_dir_z)));
	object->size[0] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_size_x)));
	object->size[1] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_size_y)));
	object->size[2] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_size_z)));
	object->c_o = ft_atoi_base(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_color)), "0123456789ABCDEF");
	object->eff[3] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_negative)));
	object->eff[0] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_transparence)));
	object->eff[1] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_reflexion)));
	object->eff[2] = ft_atoi(gtk_entry_get_text(GTK_ENTRY(raytracer->pscene_object_refraction)));
}


void		pscene_object_create(t_gen *raytracer)
{
	(void)raytracer;
}
