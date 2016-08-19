/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 20:05:03 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/18 23:55:58 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>
#include "libft.h"
#include <raystruct.h>
#include <raytra_gen.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

static void rotate(t_gen *s, int key)
{
	t_vector new;
	t_vector obj;

	if (s->to_move->type & SPHERE)
	{
		if (!s->to_move->cut)
			return ;
		new = new_vector(s->to_move->cut->pos[0], s->to_move->cut->pos[1], s->to_move->cut->pos[2]);
	}
	else if (s->to_move->type & PLAN)
		new = new_vector(s->to_move->pos[0], s->to_move->pos[1], s->to_move->pos[2]);
	// else if (s->to_move->type == CYLINDRE)
		// new = newVector(s->to_move->cut->pos[0], s->to_move->cut->pos[1], s->to_move->cut->pos[2]);
	obj = new_vector(s->to_move->pos[0], s->to_move->pos[1], s->to_move->pos[2]);
	if (key == GDK_KEY_KP_9)
	{
		new = matricerot_z(new, vector_dot(new, obj));
	}
	if (key == GDK_KEY_KP_6)
		new = matricerot_y(new, vector_dot(new, obj));
	if (key == GDK_KEY_KP_3)
		new = matricerot_x(new, vector_dot(new, obj));
	if (s->to_move->type & SPHERE)
	{
		s->to_move->cut->pos[0] = new.x;
		s->to_move->cut->pos[1] = new.y;
		s->to_move->cut->pos[2] = new.z;
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

	(void)widget;
	key = (void*)event;
	t_gen *s = user_data;
	if (!s->to_move)
		return (0);
	if (s->to_move->type & COMPLEXE)
		move_complex(s, key->keyval);
	if(key->keyval == GDK_KEY_Escape)
		exit(0);
	else if (key->keyval == GDK_KEY_s)
		s->rep ^= SAVE;
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
