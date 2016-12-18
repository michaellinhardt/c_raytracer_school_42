/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 18:07:13 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 02:38:19 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

t_vector	vector_normalize(t_vector v)
{
	double		norm;
	t_vector	result;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (norm)
	{
		result.x = v.x / norm;
		result.y = v.y / norm;
		result.z = v.z / norm;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

t_vector	new_vector(double x, double y, double z)
{
	t_vector result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

double		vector_dist(t_vector v1, t_vector v2)
{
	t_vector sub;

	sub = vector_sub(v1, v2);
	return (vector_magnitude(sub));
}

t_vector	vector_dir(t_vector v1, t_vector v2)
{
	t_vector sub;

	sub = vector_sub(v1, v2);
	sub = vector_normalize(sub);
	return (sub);
}

t_vector	get_hitpoint(t_vector start, t_vector dir, double dist)
{
	t_vector hitpoint;

	hitpoint.x = start.x + dist * dir.x;
	hitpoint.y = start.y + dist * dir.y;
	hitpoint.z = start.z + dist * dir.z;
	return (hitpoint);
}
