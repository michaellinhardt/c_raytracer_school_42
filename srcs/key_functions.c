/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 09:43:35 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/11 02:35:55 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

int		key_reaction(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

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

	if (s->to_move->type & SPHERE)
		new = new_vector(s->to_move->cut[0], s->to_move->cut[1], s->to_move->cut[2]);
	else if (s->to_move->type & PLAN)
		new = new_vector(s->to_move->pos[0], s->to_move->pos[1], s->to_move->pos[2]);
	obj = new_vector(s->to_move->pos[0], s->to_move->pos[1], s->to_move->pos[2]);
	if (key == KEY_NIN)
		new = matricerot_z(new, vector_dot(new, obj));
	if (key == KEY_SIX)
		new = matricerot_y(new, vector_dot(new, obj));
	if (key == KEY_THR)
		new = matricerot_x(new, vector_dot(new, obj));
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

int			press_key(int key, t_gen *s)
{
	if (!s->to_move)
		return (0);
	else if (key == 1)
		s->rep ^= SAVE;
	else if (key == 124)
		switch_scene(s, &s->sc);
	else if (key == 119)
		print_scene(s);
	if (s->to_move->type == COMPLEXE)
		move_complex(s, key);
	else if (key == KEY_ONE)
		s->to_move->pos[0] -= 1.0;
	else if (key == KEY_TWO)
		s->to_move->pos[0] += 1.0;
	else if (key == KEY_FOU)
		s->to_move->pos[1] -= 1.0;
	else if (key == KEY_FIV)
		s->to_move->pos[1] += 1.0;
	else if (key == KEY_SEV)
		s->to_move->pos[2] -= 1.0;
	else if (key == KEY_EIG)
		s->to_move->pos[2] += 1.0;
	else if (key == KEY_NIN || key == KEY_SIX || key == KEY_THR)
		rotate(s, key);
	raytracing(s);
	return (1);
}

