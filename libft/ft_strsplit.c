/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:02:19 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/04/17 14:00:28 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			**fill_matrix(char const *s, char c, char **split)
{
	int i;
	int j;

	j = -1;
	while (s[0] && !(i = 0))
	{
		while ((unsigned char)s[i] == (unsigned char)c)
			++i;
		s += i;
		if (!s[i])
			break ;
		i = 0;
		while (s[i] && (unsigned char)s[i] != (unsigned char)c)
			++i;
		if (i || !s[i])
		{
			++j;
			split[j] = ft_strsub(s, 0, i);
			while (s[i] && (unsigned char)s[i] == (unsigned char)c)
				++i;
			s += i;
		}
	}
	split[j + 1] = NULL;
	return (split);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**spli;

	if (s == NULL)
		return (NULL);
	if (!(spli = (char**)ft_memalloc(sizeof(char*)
		* (ft_strchr_c(s, c) + 1) * 3)))
		return (NULL);
	spli = fill_matrix(s, c, spli);
	return (spli);
}
