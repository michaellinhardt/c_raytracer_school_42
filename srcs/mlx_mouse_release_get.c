/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_release_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:58 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:58 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		prepare_data(t_get *g)
{
	char		*tmp;

	tmp = NULL;
	ft_bzero(&g->data, sizeof(g->data));
	ft_bzero(&g->tmp, sizeof(g->tmp));
	tmp = input_target_to_str(g);
	ft_memcpy(g->data, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

void			input_set_focus(t_gen *d, t_mlx *m, t_get *get, int tar)
{
	int			i;

	i = -1;
	m->getfocus = NULL;
	while (++i < GET_APP_MAX && (get = &m->get[i]))
		if (i != tar && get->status == GET_FOCUS)
		{
			get->action = GET_WAITING;
			get->status = GET_ENABLED;
		}
		else if (i == tar && get->status == GET_ENABLED && (m->getfocus = get))
		{
			get->status = GET_FOCUS;
			prepare_data(get);
			if (get->init)
				get->init((void *)d, (void *)m, (void *)get);
		}
		else if (i == tar && get->status == GET_FOCUS)
			m->getfocus = get;
}

static void		set_pos(t_get *get, int x, int max)
{
	int		start;
	int		mid;
	int		end;

	get->i = (x - INPUT_PADDING - get->box.pos[0]) / INPUT_SIZE_CHAR_X;
	start = get->i * INPUT_SIZE_CHAR_X;
	mid = start + (INPUT_SIZE_CHAR_X / 2);
	end = start + INPUT_SIZE_CHAR_X;
	if ((x - INPUT_PADDING - get->box.pos[0]) > mid)
		get->i++;
	if (get->i > max)
		get->i = max;
	scene_input_draw_cursor(NULL, NULL, NULL);
}

int				mouse_release_get(t_gen *d, int btn, int x, int y)
{
	t_get		*get;
	t_img		*img;
	int			i[2];

	i[0] = -1;
	i[1] = 0;
	while (++i[0] < GET_APP_MAX)
	{
		((get = &d->mlx.get[i[0]])->status == GET_FOCUS) ? i[1]++ : 1;
		if (area((img = &d->mlx.get[i[0]].box), NULL, x, y)
		&& (btn == 1 || btn == 2) && d->mlx.menu.draw == 1
		&& get->menu > NONE && get->menu == d->mlx.menu.id)
		{
			if (btn == 1)
			{
				if (get->status != GET_FOCUS)
					input_set_focus(d, &d->mlx, (t_get *)NULL, i[0]);
				set_pos(get, x, (int)ft_strlen(get->data));
			}
			return (1);
		}
	}
	if (i[1] > 0)
		input_set_focus(d, &d->mlx, (t_get *)NULL, -1);
	return (0);
}
