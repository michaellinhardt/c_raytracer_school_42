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
		i->inter2 = ((-b + sqrtf(discriminant)) / (2 * a));
		i->inter1 = ((-b + sqrtf(discriminant)) / (2 * a));
		return (i->inter1);
	}
	else
	{
		i->inter1 = ((-b + sqrtf(discriminant)) / (2 * a));
		i->inter2 = ((-b - sqrtf(discriminant)) / (2 * a));
		if (i->inter2 > 0 && (i->inter2 < i->inter1 || i->inter1 < 0))
		{
			discriminant = i->inter2;
			i->inter2 = i->inter1;
			i->inter1 = discriminant;
		}
		if (i->inter1 >= 0)
			return (i->inter1);
		return (0);
	}
}
