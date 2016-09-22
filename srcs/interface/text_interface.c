/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:22:01 by tiboitel          #+#    #+#             */
/*   Updated: 2016/09/22 15:28:18 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include "libft.h"

void	set_text_entry_value(GtkWidget *widget, int value)
{
	char	*str;

	str = NULL;
	str = ft_itoa(value);
	gtk_entry_set_text(GTK_ENTRY(widget), str);
	free(str);
	str = NULL;
}
