/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 17:52:47 by tiboitel          #+#    #+#             */
/*   Updated: 2016/09/17 20:14:54 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raystruct.h>
#include <raytra_gen.h>
#include "libft.h"

static void	set_text_entry_value(GtkWidget *widget, int value)
{
	char	*str;

	str = NULL;
	str = ft_itoa(value);
	gtk_entry_set_text(GTK_ENTRY(widget), str);
	free(str);
	str = NULL;
}

void		pscene_object_hydrate(t_gen *raytracer)
{
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
	(void)raytracer;
}

void		pscene_object_update(t_gen *raytracer)
{
	(void)raytracer;
}

void		pscene_object_create(t_gen *raytracer)
{
	(void)raytracer;
}
