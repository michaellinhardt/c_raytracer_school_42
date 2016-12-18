/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 23:38:00 by tiboitel          #+#    #+#             */
/*   Updated: 2016/12/18 07:29:01 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		check_num_str(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (((str[i] >= '\0' && str[i] < '0') || (str[i] > '9' && str[i] < 'A')
					|| (str[i] > 'F')) && str[i] != '-')
			return ;
		i++;
	}
}

static int		power(int n, int pow)
{
	int		a;

	if (pow == 0)
		return (1);
	a = power(n, pow / 2);
	if (pow % 2 == 0)
		return (a * a);
	else
		return (n * a * a);
}

int				ft_atoi_base(const char *str, char *base)
{
	int		dec;
	int		i;
	int		j;
	int		y;
	int		sgn;

	j = 0;
	dec = 0;
	sgn = 1;
	check_num_str(str);
	i = ft_strlen(str) - 1;
	while (str[i] && str[i] != '-' && str[i] != '+' && i >= 0)
	{
		y = 0;
		while (base[y] && str[i] != base[y])
			y++;
		if (y == (int)ft_strlen(base))
			y = 0;
		dec += y * power(ft_strlen(base), j++);
		i--;
	}
	while (str[i] && i >= 0)
		if (str[i--] == '-')
			sgn *= -1;
	return (dec * sgn);
}
