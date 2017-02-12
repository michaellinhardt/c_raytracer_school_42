/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:10 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:10 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static int		ob(t_gen *d, t_vector *vec, double multiplier, int i)
{
	if (d->mlx.menu.edit_mode & EDIT_BOOL)
	{
		vec->x = d->mlx.menu.obj->pos[3];
		vec->y = d->mlx.menu.obj->pos[4];
		vec->z = d->mlx.menu.obj->pos[5];
	}
	else
	{
		d->mlx.menu.obj->pos[i] += (multiplier * OBJ_POS_MOD);
		redraw(d, &d->mlx, 1);
		return (0);
	}
	return (1);
}

static void		apply_matrice_obj(t_gen *d, t_vector *vec
	, t_vector (*matrice)(t_vector v, double angle), double angle)
{
	t_mlx		*m;

	m = &d->mlx;
	*vec = matrice(*vec, angle);
	m->menu.obj->pos[3] = vec->x;
	m->menu.obj->pos[4] = vec->y;
	m->menu.obj->pos[5] = vec->z;
	redraw(d, &d->mlx, 1);
}

static void		keyp_hook_keyboard2(int key, t_gen *d, int mult)
{
	if (!d->sc || !d->sc->data ||
	(key != 12 && key != 13 && key != 14 && key != 0 && key != 1 && key != 2))
		return ;
	mult = (key == 12 || key == 0 || key == 1) ? -1 : 1;
	if (d->mlx.menu.edit_mode & EDIT_BOOL)
	{
		d->view_angle.x += mult * OBJ_DIR_MOD;
		d->view_angle.y += mult * OBJ_DIR_MOD;
		d->view_angle.z += mult * OBJ_DIR_MOD;
	}
	else
	{
		if (key == 0 || key == 2)
			d->sc->cam[0] += mult * OBJ_POS_MOD;
		else if (key == 13 || key == 1)
			d->sc->cam[1] += mult * OBJ_POS_MOD;
		else if (key == 12 || key == 14)
			d->sc->cam[2] += mult * OBJ_POS_MOD;
	}
	redraw(d, &d->mlx, 1);
}

int				keyp_hook_keyboard(int key, t_gen *d, t_vector vec)
{
	if (d->mlx.menu.draw == 1)
		return (0);
	if (key == 89 && d->mlx.menu.obj && ob(d, &vec, -1, 2))
		apply_matrice_obj(d, &vec, &matricerot_z, OBJ_DIR_MOD * -1);
	else if (key == 92 && d->mlx.menu.obj && ob(d, &vec, 1, 2))
		apply_matrice_obj(d, &vec, &matricerot_z, OBJ_DIR_MOD * 1);
	else if (key == 91 && d->mlx.menu.obj && ob(d, &vec, 1, 1))
		apply_matrice_obj(d, &vec, &matricerot_x, OBJ_DIR_MOD * 1);
	else if (key == 87 && d->mlx.menu.obj && ob(d, &vec, -1, 1))
		apply_matrice_obj(d, &vec, &matricerot_x, OBJ_DIR_MOD * -1);
	else if (key == 86 && d->mlx.menu.obj && ob(d, &vec, -1, 0))
		apply_matrice_obj(d, &vec, &matricerot_y, OBJ_DIR_MOD * -1);
	else if (key == 88 && d->mlx.menu.obj && ob(d, &vec, 1, 0))
		apply_matrice_obj(d, &vec, &matricerot_y, OBJ_DIR_MOD * 1);
	else
		keyp_hook_keyboard2(key, d, 0);
	return (0);
}
