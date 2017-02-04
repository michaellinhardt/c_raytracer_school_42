/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:31 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:31 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		set_filter_text2(char *msg, int i)
{
	if (i == 11)
		ft_strcpy(msg, TXT_FILTER_12);
	else if (i == 12)
		ft_strcpy(msg, TXT_FILTER_13);
	else
		ft_strcpy(msg, TXT_FILTER_14);
}

static void		set_filter_text(char *msg, int i)
{
	if (i == 0)
		ft_strcpy(msg, TXT_FILTER_1);
	else if (i == 1)
		ft_strcpy(msg, TXT_FILTER_2);
	else if (i == 2)
		ft_strcpy(msg, TXT_FILTER_3);
	else if (i == 3)
		ft_strcpy(msg, TXT_FILTER_4);
	else if (i == 4)
		ft_strcpy(msg, TXT_FILTER_5);
	else if (i == 5)
		ft_strcpy(msg, TXT_FILTER_6);
	else if (i == 6)
		ft_strcpy(msg, TXT_FILTER_7);
	else if (i == 7)
		ft_strcpy(msg, TXT_FILTER_8);
	else if (i == 8)
		ft_strcpy(msg, TXT_FILTER_9);
	else if (i == 9)
		ft_strcpy(msg, TXT_FILTER_10);
	else if (i == 10)
		ft_strcpy(msg, TXT_FILTER_11);
	else
		set_filter_text2(msg, i);
}

static void		filter_text(t_mlx *m, int i, t_img *img)
{
	char	msg[255];

	while (++i < 14)
	{
		set_filter_text(msg, i);
		img = &m->scene_img[1][IB_FILTER1_OFF + i];
		mlx_string_put(m->mlx, m->win
		, img->pos[0] + 40, img->pos[1] + 6, 0xFFFFFF, msg);
	}
}

void			scene_text(t_gen *d, t_mlx *m)
{
	if (m->scene == RT && m->menu.draw == 1)
	{
		scene_text_menu(d, m);
		scene_text_input(m, (t_get *)NULL, -1);
		scene_text_notif(m, m->notif);
		if (m->menu.id == LOAD_FILTER)
			filter_text(m, -1, (t_img *)NULL);
	}
}
