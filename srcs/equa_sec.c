/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equa_sec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 16:54:30 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 18:04:16 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double	equa_sec(double a, double b, double discriminant, t_inter *i)
{
	if (discriminant == 0)
	{
		i->hit2 = ((-b + sqrtf(discriminant)) / (2 * a));
		i->hit1 = ((-b + sqrtf(discriminant)) / (2 * a));
		return (i->hit1);
	}
	else
	{
		i->hit1 = ((-b + sqrtf(discriminant)) / (2 * a));
		i->hit2 = ((-b - sqrtf(discriminant)) / (2 * a));
		if (i->hit2 > 0 && (i->hit2 < i->hit1 || i->hit1 < 0))
		{
			discriminant = i->hit2;
			i->hit2 = i->hit1;
			i->hit1 = discriminant;
		}
		if (i->hit1 >= 0)
			return (i->hit1);
		return (0);
	}
}
