/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_text_menu_bis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:25 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:26 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void		scene_text_menu_load(t_mlx *m, t_flst *elem, int i, int color)
{
	char			name[MENU_LOAD_PREVIEW_NAME_SIZE_MAX];
	size_t			len;

	while (elem && ++i < MENU_LOAD_X_MAX * MENU_LOAD_Y_MAX)
	{
		if (!elem->path && ((elem = elem->n) || 1))
			continue ;
		if ((len = ft_strlen(elem->path)) > MENU_LOAD_PREVIEW_NAME_SIZE_MAX)
		{
			ft_memset(name, '.', MENU_LOAD_PREVIEW_NAME_SIZE_MAX);
			ft_memcpy(name, elem->path, MENU_LOAD_PREVIEW_NAME_SIZE_MAX - 2);
			len = MENU_LOAD_PREVIEW_NAME_SIZE_MAX;
		}
		else
			ft_memcpy(name, elem->path, len);
		name[len] = '\0';
		color = 0xFFFFFF;
		if (elem->actif == 1)
			color = 0xFF0000;
		else if (elem->over)
			color = 0x00FFFF;
		mlx_string_put(m->mlx, m->win, elem->top[0] + MENU_LOAD_TEXT_MARGIN_X,
		elem->bot[1] + MENU_LOAD_TEXT_MARGIN_Y, color, name);
		elem = elem->n;
	}
}

void		scene_text_camera(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_CAMERA_BOX].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_CAMERA_BOX].pos[1] + 25
	, c, TXT_CAMERA_MOD_TITLE);
}

void		scene_text_scene_del(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_SCENE_BOX_DEL].pos[1] + 38
	, c, TXT_SCENE_DEL_VALID);
}

void		scene_text_object_del(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[1] + 38
	, c, TXT_OBJECT_DEL_VALID);
}

void		scene_text_spot_del(t_mlx *m, int c)
{
	mlx_string_put(m->mlx, m->win
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[0] + 20
	, m->scene_img[1][IMENU_EDIT_OBJECT_BOX_DEL].pos[1] + 38
	, c, TXT_SPOT_DEL_VALID);
}
