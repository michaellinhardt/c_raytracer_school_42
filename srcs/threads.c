/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 17:20:00 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/12 13:55:33 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void		init_threads(t_thread *thread, t_gen *s)
{
	int i;
	int j;
	int k;

	i = 0;
	j = W_X / sqrt(MT);
	k = W_Y / sqrt(MT);
	while (i < MT)
	{
		thread[i].nb = i;
		thread[i].lim[0] = i % (int)sqrt(MT) * j;
		thread[i].lim[1] = (int)(i / sqrt(MT)) * k;
		thread[i].lim[2] = i % (int)sqrt(MT) * j + j;
		thread[i].lim[3] = (int)(i / sqrt(MT)) * k + k;
		thread[i].s = s;
		++i;
	}
}
