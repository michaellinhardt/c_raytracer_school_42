/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_input_char_next.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlinhard <mlinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:48:31 by mlinhard          #+#    #+#             */
/*   Updated: 2017/02/04 13:48:31 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytra_gen.h"
#include "raystruct.h"

static void		input_catch_char_string_file(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (ft_isdigit(c) || ft_isalpha(c) || c == '.' || c == '-' || c == '_')
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
}

static void		input_catch_char_double(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (c == ',')
		c = '.';
	if (ft_isdigit(c) || (c == '.' && !ft_strchr(g->data, '.'))
	|| (c == '-' && g->i == 0 && g->data[1] != '-' && g->data[0] != '-'))
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else if (c == '.' && ft_strchr(g->data, '.'))
		notif(m, N_WARNING, "there is already a . in the input");
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
	(void)m;
}

static void		input_catch_char_int(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (ft_isdigit(c) || (c == '-' && g->i == 0 && g->data[1] != '-'
	&& g->data[0] != '-'))
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
	(void)m;
}

static void		input_catch_char_hexa(t_mlx *m, t_get *g, char c)
{
	char			*msg;
	static char		str[2] = " \0";

	if (ft_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
	{
		g->action = GET_CHAR;
		g->c = c;
	}
	else
	{
		str[0] = c;
		msg = ft_strjoin(str, " is invalid char for this input");
		notif(m, N_WARNING, msg);
		ft_strdel(&msg);
	}
	(void)m;
}

void			input_catch_char_end(t_mlx *m, t_get *g, char c)
{
	if (g->mode == MODE_DOUBLE)
		input_catch_char_double(m, g, c);
	else if (g->mode == MODE_DOUBLE_BUT_INT)
		input_catch_char_int(m, g, c);
	else if (g->mode == MODE_INT)
		input_catch_char_int(m, g, c);
	else if (g->mode == MODE_HEXA || g->mode == MODE_HEXA_TO_DOUBLE)
		input_catch_char_hexa(m, g, c);
	else if (g->mode == MODE_STRING)
		input_catch_char_string_file(m, g, c);
	else if (g->mode == MODE_STRING_FILE)
		input_catch_char_string_file(m, g, c);
}
