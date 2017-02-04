/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:20 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:20 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			anim_init(t_img *img, enum e_anim anim)
{
	img->anim.id = anim;
	img->anim.tempo = MENU_FADE_TEMPO;
	if (img->anim.id == FADE_IN)
		img->fade = 255;
	else if (img->anim.id == FADE_OUT)
		img->fade = 0;
}

void			scene_img_init(t_gen *d, t_mlx *m)
{
	if (m->scene == INTRO)
		scene_init_0_intro(m, (t_img *)NULL);
	else if (m->scene == RT)
		scene_init_1_rt(d, m, (t_img *)NULL);
}
