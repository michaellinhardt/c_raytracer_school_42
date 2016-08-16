/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 19:51:51 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/16 10:46:09 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "raytra_gen.h"

typedef struct		s_line
{
	char			*str;
	void			*next;
}					t_line;

void				camera(int fd, double *cam, char c);
int					verif_double(char *str);
int					verif_str(char *str, int i);
void				ambiance(int *amb, char *line);
void				color(int fd, int *color, char c, t_obj *o);
void				size(int fd, double *size);
void				effect(int fd, double *eff);
void				objects(t_scene *tmp, int fd, char *line);
char				*name(int fd);
int					type(int fd);
void				triangle(int fd, t_obj **o, char *line);

#endif
