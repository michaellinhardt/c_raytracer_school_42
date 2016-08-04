/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 19:51:10 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/04 20:57:18 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <h_gui.h>
#include <h_raystruct.h>
#include <h_raytra_gen.h>

void			on_destroy_callback(GtkWidget *pwidget, gpointer *data)
{
	(void)data;
	gtk_widget_destroy(pwidget);
	gtk_main_quit();
	// Add raytracer destructor here. 
	exit(1);
}

t_gui_handler	*gui_create(void)
{
	t_gui_handler	*handler;

	handler = NULL;
	if (!(handler = ft_memalloc(sizeof(t_gui_handler))))
		return (NULL);
	return (handler);
}

int				gui_init(t_gui_handler *handler)
{
	gtk_init(0, NULL);
	gui_create_window(handler);
	printf("Windw: %p\n", handler->pwindow);
	gtk_widget_show_all(handler->pwindow);
	gtk_main();
	gtk_widget_destroy(handler->pwindow);
	free(handler);
	return (1);
}

void			gui_create_window(t_gui_handler *handler)
{
	if (!(handler->pwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL)))
	{
		ft_putendl("LOL TA WINDOW EST KS");
		return ;
	}
	gtk_window_set_position(GTK_WINDOW(handler->pwindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(handler->pwindow), "Gestionnaire Raytracer");
	gtk_window_set_default_size(GTK_WINDOW(handler->pwindow), 480, 680);
	g_signal_connect(G_OBJECT(handler->pwindow), "destroy", G_CALLBACK(on_destroy_callback), handler);
}
