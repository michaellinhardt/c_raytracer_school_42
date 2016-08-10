/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 18:07:13 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/10 21:44:53 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double		vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	vectordivby_scalar(t_vector v, double scalar)
{
	t_vector result;

	result.x = v.x / scalar;
	result.y = v.y / scalar;
	result.z = v.z / scalar;
	return (result);
}

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.y * v2.z - v2.y * v1.z;
	result.y = v1.z * v2.x - v2.z * v1.x;
	result.z = v1.x * v2.y - v2.x * v1.y;
	return (result);
}

t_vector	vectormultby_scalar(t_vector v, double scalar)
{
	t_vector result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

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
