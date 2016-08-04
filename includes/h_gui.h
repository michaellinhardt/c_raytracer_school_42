/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_gui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 19:53:30 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/04 20:18:15 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GUI_H
# define FT_GUI_H
#include <gtk/gtk.h>

typedef struct	s_gui_handler
{
	GtkWidget	*pwindow;

}				t_gui_handler;

t_gui_handler	*gui_create(void);
int				gui_init(t_gui_handler *handler);
void			gui_create_window(t_gui_handler *handler);

/*
 ** @Callback section.
 */
void			on_destroy_callback(GtkWidget *pwidget, gpointer *data);
#endif
