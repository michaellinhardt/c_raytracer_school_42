/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 19:01:38 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/01/16 00:15:52 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_afterpoint(double n, int ps, int p, long long int *j)
{
	unsigned long long int	k;
	long long int			l;

	(void)p;
	if (n < 0)
		n = -n;
	k = (n - *j) * ps * 10;
	*j = (n - *j) * ps;
	l = ft_sizeintu(ps) - ft_sizeint(*j) - 2;
	if ((k % 10) >= 5)
		++(*j);
}

static char	*end(int l, char *str, char *temp, int j)
{
	char *tmp;

	while (l > 0)
	{
		tmp = str;
		str = ft_strjoin(str, "0");
		ft_strdel(&tmp);
		l--;
	}
	tmp = str;
	temp = ft_itoa(j);
	str = ft_strjoin(str, temp);
	ft_strdel(&tmp);
	ft_strdel(&temp);
	return (str);
}

static char	*ft_transformation(unsigned long long int ps, long long int k,
	long long int j, double n)
{
	char	*str;
	char	*tmp;
	char	*temp;
	int		l;

	l = ft_sizeintu(ps) - ft_sizeintu(j) - 1;
	str = (n < 0 && k == 0) ? ft_strdup("-") : ft_strnew(1);
	if (l < -1)
	{
		(k > 0) ? k++ : k--;
		j = 0;
		l = ft_sizeintu(ps) - ft_sizeintu(j) - 1;
	}
	tmp = str;
	temp = ft_itoa(k);
	str = ft_strjoin(str, temp);
	ft_strdel(&tmp);
	ft_strdel(&temp);
	tmp = str;
	str = ft_strjoin(str, ".");
	ft_strdel(&tmp);
	return (end(l, str, temp, j));
}

char		*ft_putfloat(double n, int p)
{
	long long int			j;
	unsigned long long int	ps;
	long long int			k;

	ps = 1;
	if (p > 9)
		p = 9;
	if (p == -1 || !p)
		p = 6;
	while (p != 0)
	{
		ps = ps * 10;
		--p;
	}
	if (ps == 1 || p > 9)
		ps = 1000000;
	j = n;
	k = j;
	if (n < 0)
		j = -j;
	ft_afterpoint(n, ps, p, &j);
	return (ft_transformation(ps, k, j, n));
}
