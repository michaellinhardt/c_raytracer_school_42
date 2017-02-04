/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_free_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:10 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:10 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_list_free(t_mlx *m, t_flst *flst, t_flst *destroy)
{
	if (!flst)
		return ;
	while (flst)
	{
		destroy = flst;
		flst = flst->n;
		ft_strdel(&destroy->path);
		ft_strdel(&destroy->path_preview);
		if (destroy->preview.img)
			mlx_destroy_image(m->mlx, destroy->preview.img);
		destroy->n = NULL;
		destroy->p = NULL;
		ft_memdel((void **)&destroy);
	}
	m->flst = (t_flst *)NULL;
}
