/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 13:50:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/04 13:40:49 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"
#define RAD_TO_DEG (180 / PI)
#define DEG_TO_RAD (PI / 180)

t_vector	matricerot_x(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x;
	result.y = v.y * cos(DEG_TO_RAD * angle) + v.z * -sin(DEG_TO_RAD * angle);
	result.z = v.y * sin(DEG_TO_RAD * angle) + v.z * cos(DEG_TO_RAD * angle);
	return (result);
}

t_vector	matricerot_y(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x * cos(DEG_TO_RAD * angle) + v.z * sin(DEG_TO_RAD * angle);
	result.y = v.y;
	result.z = v.x * -sin(DEG_TO_RAD * angle) + v.z * cos(DEG_TO_RAD * angle);
	return (result);
}

t_vector	matricerot_z(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x * cos(DEG_TO_RAD * angle) + v.y * -sin(DEG_TO_RAD * angle);
	result.y = v.x * sin(DEG_TO_RAD * angle) + v.y * cos(DEG_TO_RAD * angle);
	result.z = v.z;
	return (result);
}
