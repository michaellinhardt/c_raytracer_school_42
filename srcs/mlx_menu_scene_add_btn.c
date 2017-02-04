/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu_scene_add_btn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:49:32 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:49:33 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			menu_scene_add_btn_ok(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	if (!m->menu.new_scene || !ft_strcmp(m->menu.new_scene
	, TXT_SCENE_ADD_NAME_DEFAUT))
		notif(m, N_WARNING, "you must enter a new scene name");
	else if (ft_strlen(m->menu.new_scene) < 3)
		notif(m, N_WARNING, "scene name must have at least 3 char");
	else
	{
		parse_scene(d, PATH_NEW_SCENE);
		ft_strdel(&d->sc->name);
		d->sc->name = ft_strdup(m->menu.new_scene);
		d->sc->path_save = NULL;
		m->menu.draw = -1;
	}
}
