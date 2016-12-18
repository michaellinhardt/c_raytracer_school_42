/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_next.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 02:37:01 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 02:38:23 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	vector_mult(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}

t_vector	vector_rev(t_vector v)
{
	t_vector result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}

double		vector_magnitude(t_vector v)
{
	return (sqrtf(vector_dot(v, v)));
}
