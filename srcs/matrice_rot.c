/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 13:50:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/10 22:58:37 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

t_vector	matricerot_x(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x;
	result.y = v.y * cos(angle) + v.z * -sin(angle);
	result.z = v.y * sin(angle) + v.z * cos(angle);
	return (result);
}

t_vector	matricerot_y(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x * cos(angle) + v.z * sin(angle);
	result.y = v.y;
	result.z = v.x * -sin(angle) + v.z * cos(angle);
	return (result);
}

t_vector	matricerot_z(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x * cos(angle) + v.y * -sin(angle);
	result.y = v.x * sin(angle) + v.y * cos(angle);
	result.z = v.z;
	return (result);
}
