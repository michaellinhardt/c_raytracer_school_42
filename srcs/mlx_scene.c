/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:33 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:33 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void		scene(t_gen *d, t_mlx *m)
{
	if (m->scene == INTRO)
		scene_0_intro(m);
	else if (m->scene == RT)
		scene_1_rt(d, m);
}
