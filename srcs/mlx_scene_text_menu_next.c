/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_scene_text_menu_next.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:50:27 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:50:28 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void		scene_text_object_mod2(t_mlx *m, int c, int i, t_img *img)
{
	char		str[9][255];

	ft_strcpy(str[0], TXT_OBJECT_TYPE_SPHERE);
	ft_strcpy(str[1], TXT_OBJECT_TYPE_RECTANGLE);
	ft_strcpy(str[2], TXT_OBJECT_TYPE_PLAN);
	ft_strcpy(str[3], TXT_OBJECT_TYPE_CONE);
	ft_strcpy(str[4], TXT_OBJECT_TYPE_CYLINDRE);
	ft_strcpy(str[5], TXT_OBJECT_TYPE_COMPLEXE);
	ft_strcpy(str[6], TXT_OBJECT_TYPE_BOLOID);
	ft_strcpy(str[7], TXT_OBJECT_TYPE_TRIANGLE);
	ft_strcpy(str[8], TXT_OBJECT_TYPE_ELLIPSE);
	while (++i < 10)
	{
		img = &m->scene_img[1][(IB_OBJECT_MOD_TYPE_SELECT + i)];
		mlx_string_put(m->mlx, m->win, img->pos[0] + 10, img->pos[1] + 10
		, c, str[i - 1]);
	}
}

void		scene_text_spot_mod2(t_mlx *m, int c, int i, t_img *img)
{
	char		str[2][255];

	ft_strcpy(str[0], TXT_SPOT_TYPE_DIIR);
	ft_strcpy(str[1], TXT_SPOT_TYPE_POINT);
	while (++i < 3)
	{
		img = &m->scene_img[1][(IMENU_EDIT_SPOT_BOX + i)];
		mlx_string_put(m->mlx, m->win, img->pos[0] + 10, img->pos[1] + 10
		, c, str[i - 1]);
	}
}

void		scene_text_spot_mod(t_mlx *m, int c, char msg[512])
{
	mlx_string_put(m->mlx, m->win, m->get[ID_INPUT_SPOT_POS1].box.pos[0]
	+ INPUT_NAME_POS_X, m->get[ID_INPUT_SPOT_POS4].box.pos[1] + 15
	+ m->get[ID_INPUT_OBJECT_POS4].box.heigh, c, TXT_SPOT_MOD_TYPE);
	if (m->menu.spot->type == DIIR)
		ft_strcpy(msg, TXT_SPOT_TYPE_DIIR);
	else
		ft_strcpy(msg, TXT_SPOT_TYPE_POINT);
	mlx_string_put(m->mlx, m->win, m->get[ID_INPUT_SPOT_POS1].box.pos[0]
	+ INPUT_NAME_POS_X + 130, m->get[ID_INPUT_SPOT_POS4].box.pos[1] + 15
	+ m->get[ID_INPUT_SPOT_POS4].box.heigh, c, msg);
	scene_text_spot_mod2(m, c, 0, (t_img *)NULL);
}
