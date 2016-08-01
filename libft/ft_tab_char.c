/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 22:48:03 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/04/17 02:27:11 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_char(int line, int *col)
{
	char	**tab;
	int		i;

	tab = (char**)malloc(sizeof(char*) * (line + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	(void)col;
	while (i < line)
	{
		if (col[0] < 0)
			tab[i] = ft_strnew(-col[0]);
		else
			tab[i] = ft_strnew(col[i]);
		if (tab[i] == NULL)
			return (NULL);
		++i;
	}
	tab[i] = NULL;
	tab[i + 1] = NULL;
	return (tab);
}
