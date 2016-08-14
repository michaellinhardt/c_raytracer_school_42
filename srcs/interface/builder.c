/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 02:10:37 by tiboitel          #+#    #+#             */
/*   Updated: 2016/08/12 06:33:29 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include "libft.h"
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>


static void	switch_scene(t_gen *s, t_scene **first)
{
	t_scene *tmp;
	t_scene *temp;

	if (!s->sc->next)
		return ;

	tmp = *first;
	*first = (*first)->next;
	temp = *first;
	while (temp->next)
		temp = temp->next;
	tmp->next = NULL;
	temp->next = tmp;
}	

static void rotate(t_gen *s, int key)
{
	t_vector new;
	t_vector obj;

	if (s->to_move->type == SPHERE)
		new = newVector(s->to_move->cut[0], s->to_move->cut[1], s->to_move->cut[2]);
	else if (s->to_move->type == PLAN)
		new = newVector(s->to_move->pos[0], s->to_move->pos[1], s->to_move->pos[2]);
	// else if (s->to_move->type == CYLINDRE)
		// new = newVector(s->to_move->cut[0], s->to_move->cut[1], s->to_move->cut[2]);
	obj = newVector(s->to_move->pos[0], s->to_move->pos[1], s->to_move->pos[2]);
	if (key == KEY_NIN)
		new = MatricerotZ(new, vectorDot(new, obj));
	if (key == KEY_SIX)
		new = MatricerotY(new, vectorDot(new, obj));
	if (key == KEY_THR)
		new = MatricerotX(new, vectorDot(new, obj));
	if (s->to_move->type == SPHERE)
	{
		s->to_move->cut[0] = new.x;
		s->to_move->cut[1] = new.y;
		s->to_move->cut[2] = new.z;
	}
	else
	{
		s->to_move->pos[0] = new.x;
		s->to_move->pos[1] = new.y;
		s->to_move->pos[2] = new.z;
	}
}

void		move_complex(t_gen *s, int key)
{
	t_obj *tmp;

	tmp = s->to_move->comp;
	while (tmp)
	{
		if (key == KEY_ONE)
			tmp->pos[0] -= 1.0;
		else if (key == KEY_TWO)
			tmp->pos[0] += 1.0;
		else if (key == KEY_FOU)
			tmp->pos[1] -= 1.0;
		else if (key == KEY_FIV)
			tmp->pos[1] += 1.0;
		else if (key == KEY_SEV)
			tmp->pos[2] -= 1.0;
		else if (key == KEY_EIG)
			tmp->pos[2] += 1.0;
		tmp = tmp->next;
	}
}

G_MODULE_EXPORT	gboolean	on_key_press(GtkWidget *widget, GdkEvent  *event, void *user_data)
{
	GdkEventKey *key;
	(void)user_data;
	(void)widget;
	key = (void*)event;

	t_gen *s = user_data;

	if (!s->to_move)
		return (0);
	if (s->to_move->type == COMPLEXE)
		move_complex(s, key->keyval);
	if(key->keyval == GDK_KEY_Escape)
		exit(0);
	else if (key->keyval == GDK_KEY_s)
		s->rep ^= SAVE;
	else if (key->keyval == GDK_KEY_Right)
		switch_scene(s, &s->sc);
	else if (key->keyval ==  GDK_KEY_End)
		print_scene(s);
	else if (key->keyval == GDK_KEY_KP_1)
		s->to_move->pos[0] -= 1.0;
	else if (key->keyval == GDK_KEY_KP_2)
		s->to_move->pos[0] += 1.0;
	else if (key->keyval == GDK_KEY_KP_4)
		s->to_move->pos[1] -= 1.0;
	else if (key->keyval == GDK_KEY_KP_5)
		s->to_move->pos[1] += 1.0;
	else if (key->keyval == GDK_KEY_KP_7)
		s->to_move->pos[2] -= 1.0;
	else if (key->keyval == GDK_KEY_KP_8)
		s->to_move->pos[2] += 1.0;
	else if (key->keyval == GDK_KEY_KP_3 || key->keyval == GDK_KEY_KP_6 || key->keyval == GDK_KEY_KP_9)
		rotate(s, key->keyval);
	raytracing(s);
	return 0;	
}

G_MODULE_EXPORT void	pscene_button_save_clicked(GtkWidget *pwidget, gpointer data)
{
	(void)pwidget;
	(void)data;
}

G_MODULE_EXPORT void	on_pscene_object_select_changed(GtkWidget *pwidget, gpointer data)
{
	t_gen	*raytracer;
	char	*objname;
	t_obj	*tmp;

	(void)pwidget;
	raytracer = NULL;
	if (!data)
	{
		error(4, "unable to get pointer to raytracer\n");
	}
	raytracer = (t_gen *)data;
	objname = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
	if (!objname)
		return ;
	tmp = raytracer->sc->obj;
	while (tmp)
	{
		if (!ft_strcmp(objname, tmp->name))
			raytracer->to_move = tmp;
		tmp = tmp->next;
	}
}

G_MODULE_EXPORT void	on_pscene_current_scene_changed(GtkWidget *pwidget, gpointer data)
{
	t_scene		*head;
	t_scene		*tmp;
	char		*current;
	t_gen		*raytracer;

	tmp = NULL;
	current = NULL;
	raytracer = NULL;
	if (data == NULL)
	{
		error(4, "Unable to get pointer to raytracer\n");
		return ;
	}
	raytracer = (t_gen *)data;
	head = raytracer->sc;
	tmp = raytracer->sc;
	current = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(
				raytracer->pscene_current_scene));
	if (!current)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, current) == 0)
		{
			raytracer->sc = tmp;
			raytracer->to_move = NULL;
			t_obj	*otmp;

			gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
			otmp = raytracer->sc->obj;
			/* Redondance de code avec button_load, isoler les acteurs */
			while (otmp)
			{
				gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select),
						NULL, otmp->name);
				otmp = otmp->next;
			}
			/* Fin de la redondance */
			raytracing(raytracer);
		}
		tmp = tmp->next;
	}
	raytracer->sc = head;
	(void)pwidget;
	(void)data;
}

G_MODULE_EXPORT void	pscene_button_load_clicked(GtkWidget *pwidget, gpointer data)
{
	t_gen			*raytracer;
	char			*filename;
	GtkFileChooser	*chooser;
	t_scene			*tmp;	
	t_obj	*otmp;

	(void)pwidget;
	if (!data)
	{
		error(4, "Unable to get pointer to raytracer\n");
		return ;
	}
	raytracer = NULL;
	filename = NULL;
	chooser = NULL;
	tmp = NULL;
	raytracer = (t_gen *)data;
	raytracer->to_move = NULL;
	chooser = GTK_FILE_CHOOSER(raytracer->pscene_choosefile);
	filename = gtk_file_chooser_get_filename(chooser);
	parse_scene(raytracer, filename);
	/*
	 ** @Ajout des elements au combo box.
	 */	
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_current_scene));
	tmp = raytracer->sc;
	while (tmp)
	{
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_current_scene),
				NULL, tmp->name);
		tmp = tmp->next;
	}
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select));
	otmp = raytracer->sc->obj;
	while (otmp)
	{
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(raytracer->pscene_object_select),
				NULL, otmp->name);
		otmp = otmp->next;
	}
	/*
	 ** @Lancement de l'affichage.
	 */
	raytracing(raytracer);
	g_free(filename);
}

G_MODULE_EXPORT void	on_pwindow_destroy(GtkWidget *pwidget, gpointer data)
{
	(void)data;
	gtk_widget_destroy(pwidget);
	gtk_main_quit();
}

int		load_interface(t_gen *raytracer)
{
	GtkBuilder	*builder;
	GError		*err;
	GdkPixbuf 	*pixbuf;
	unsigned char *data;

	err = NULL;
	builder = NULL;	
	gtk_init(0, NULL);
	builder = gtk_builder_new();
	if (builder == NULL)
		return (0);
	gtk_builder_add_from_file(builder, "resources/interface.glade", &err);
	if (err != NULL)
	{
		g_error("%s", err->message);
		g_error_free(err);
		return (0);
	}
	CH_GET_WIDGET(builder, pwindow, raytracer);
	CH_GET_WIDGET(builder, pdrawarea, raytracer);
	CH_GET_WIDGET(builder, pscene_choosefile, raytracer);
	CH_GET_WIDGET(builder, pscene_current_scene, raytracer);
	CH_GET_WIDGET(builder, pscene_object_select, raytracer);
	if (!(data = ft_memalloc(1680 * 24 * 1050)))
		return (0);
	pixbuf = gtk_new_image(data, 1680, 1050);
	gtk_put_image_to_window(GTK_IMAGE(raytracer->pdrawarea), pixbuf);
	gtk_builder_connect_signals(builder, raytracer);		
	g_object_unref(pixbuf);
	g_object_unref(builder);
	free(data);
	return (1);
}
