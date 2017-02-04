/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_notif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:03 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:03 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		notif_free(t_mlx *m, t_notif *destroy)
{
	ft_strdel(&destroy->msg);
	destroy->next = NULL;
	ft_memdel((void **)&destroy);
	(void)m;
}

void			scene_text_notif(t_mlx *m, t_notif *lst)
{
	char		*strid;
	char		*tmp;

	while (lst)
	{
		strid = ft_itoa(lst->id);
		tmp = strid;
		strid = ft_strjoin(" .", tmp);
		mlx_string_put(m->mlx, m->win, lst->bloc.pos[0] + lst->bloc.width - 1
		, lst->bloc.pos[1] + 1, lst->color, strid);
		mlx_string_put(m->mlx, m->win, lst->bloc.pos[0] + NOTIF_PADDING + 5
		, lst->bloc.pos[1], lst->color, lst->msg);
		lst = lst->next;
		ft_strdel(&strid);
		ft_strdel(&tmp);
	}
}

void			notif_draw(t_mlx *m, t_notif *lst, t_notif *next)
{
	int			i;
	t_notif		*prev;

	if (!(prev = NULL) && !m->notif)
		return ;
	i = -1;
	while (lst)
	{
		next = lst->next;
		if (++i < NOTIF_PER_SCREEN && (lst->bloc.pos[0] = NOTIF_POS_RIGHT_X
		- lst->bloc.width - NOTIF_ID_SIZE_X))
			lst->bloc.pos[1] = NOTIF_POS_RIGHT_Y - (lst->bloc.heigh * i);
		else
		{
			if (!lst->next)
			{
				notif_free(m, lst);
				if (prev)
					prev->next = NULL;
			}
		}
		prev = lst;
		lst = next;
	}
}

void			notif2(t_mlx *m, enum e_notif type, char *str1, char *str2)
{
	char	*msg;

	msg = ft_strjoin(str1, str2);
	notif(m, type, msg);
	ft_strdel(&msg);
}

void			notif(t_mlx *m, enum e_notif type, char *msg)
{
	t_notif		*n;
	static int	id = -1;
	char		max[NOTIF_SIZE_MAX];

	if (!(n = (t_notif *)ft_memalloc((sizeof(t_notif)))))
		error(2, "ft_memalloc()");
	n->id = ++id;
	ft_memset(max, '.', NOTIF_SIZE_MAX - 1);
	max[NOTIF_SIZE_MAX - 1] = '\0';
	if ((int)ft_strlen(msg) + 2 > NOTIF_SIZE_MAX)
		ft_memcpy(max, msg, NOTIF_SIZE_MAX - 3);
	else
		ft_strcpy(max, msg);
	n->msg = ft_strdup(max);
	n->type = type;
	n->bloc.width = ((int)ft_strlen(n->msg) * NOTIF_SIZE_CHAR_X)
	+ (NOTIF_PADDING * 2);
	n->bloc.heigh = NOTIF_SIZE_CHAR_Y + (NOTIF_PADDING * 2);
	n->next = m->notif;
	if ((m->notif = n) && type == N_NORMAL)
		n->color = NOTIF_COLOR_NORMAL;
	else if (type == N_WARNING)
		n->color = NOTIF_COLOR_WARNING;
	else if (type == N_ERROR)
		n->color = NOTIF_COLOR_ERROR;
}
