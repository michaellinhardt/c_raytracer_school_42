/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 00:16:51 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 00:18:03 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

void			init_var_d(double *d, double x, double y, double z)
{
	d[0] = x - floor(x);
	d[1] = y - floor(y);
	d[2] = z - floor(z);
}

void			init_var_i(int *i, double x, double y, double z)
{
	i[0] = (int)floor(x) & 255;
	i[1] = (int)floor(y) & 255;
	i[2] = (int)floor(z) & 255;
}
