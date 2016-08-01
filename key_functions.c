/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 09:43:35 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/27 17:23:30 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

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
	if (key == KEY_ONE)
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

int			release_key(int key, t_gen *s)
{
	if (!s->to_move)
		return (0);
	(void)key;
	return (1);
}