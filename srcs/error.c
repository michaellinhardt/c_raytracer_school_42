/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 23:38:55 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/11 02:52:56 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"

void		error(int i, char *str)
{
	if (!i)
		ft_printf("{CREDWrong file}\n");
	if (i == 1)
		ft_printf("Missing {CRED%s} part\n", str);
	if (i == 2)
		ft_printf("{CRED%s} failed\n", str);
	if (i == 3)
		ft_printf("Wrong format for {CRED%s}\n", str);
	if (i == 4)
		ft_printf("%s", str);
	exit(1);
}
