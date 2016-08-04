/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 04:26:54 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/21 04:29:21 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_parse.h"

int			verif_str(char *str, int i)
{
	if (ft_strchr_c(str, '{') != i || ft_strchr_c(str, '}') != i)
		return (0);
	return (1);
}

int			verif_double(char *str)
{
	int i;
	int point;

	i = -1;
	point = 0;
	if (str[0] == '-' || str[0] == '+')
		++i;
	while (str[++i] && point < 2)
	{
		if (str[i] == '.')
			point++;
		else if (ft_isdigit(str[i]))
			;
		else
			break ;
	}
	if (str[i])
		return (0);
	return (1);
}
