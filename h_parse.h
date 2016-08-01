/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_parse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 19:51:51 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/21 06:52:02 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PARSE_H
# define H_PARSE_H

# include "h_raytra_gen.h"

void		camera(int fd, double *cam, char c);
int			verif_double(char *str);
int			verif_str(char *str, int i);
void		ambiance(int *amb, char *line);
void		color(int fd, int *color, char c);
void		size(int fd, double *size);
void		effect(int fd, double *eff);
void		objects(t_scene *tmp, int fd, char *line);
char		*name(int fd);
char		type(int fd);

#endif
