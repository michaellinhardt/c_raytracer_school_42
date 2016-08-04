/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 17:20:00 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/24 17:43:14 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

void		init_threads(t_thread *t, t_id *t_g, t_gen *s)
{
	int i;
	int j;
	int k;

	i = 0;
	j = W_X / sqrt(MT);
	k = W_Y / sqrt(MT);
	while (i < MT)
	{
		t[i].nb = i;
		t[i].lim[0] = i % (int)sqrt(MT) * j;
		t[i].lim[1] = (int)(i / sqrt(MT)) * k;
		t[i].lim[2] = i % (int)sqrt(MT) * j + j;
		t[i].lim[3] = (int)(i / sqrt(MT)) * k + k;
		t[i].t = t_g;
		t[i].s = s;
		++i;
	}
}
