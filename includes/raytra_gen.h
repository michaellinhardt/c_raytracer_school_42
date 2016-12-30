/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytra_gen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:12:41 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/30 22:39:47 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRA_GEN_H
# define RAYTRA_GEN_H

# include "libft.h"
# include "mlx_struct.h"
# include "get_next_line.h"
# include <mlx.h>
// # include <gtk/gtk.h>
// # include <glib.h>
# include <math.h>

/*
**	BOOL pour les objets
*/

# define SPHERE 0x1
# define RECTANGLE 0x2
# define PLAN 0x4
# define CONE 0x8
# define CYLINDRE 0x10
# define COMPLEXE 0x20
# define BOLOID 0x80
# define TRIANGLE 0x100
# define ELLIPSE 0x200

/*
**	BOOL pour les textures
*/

# define EARTH 0x1
# define FIRE 0x2
# define BLACK 0x4
# define ICE 0x8

/*
**	BOOL pour les spots
*/

# define DIR 0x1
# define POINT 0x2

# define SAVE 0x1

typedef struct		s_vector
{
	double				x;
	double				y;
	double				z;
}					t_vector;

typedef struct		s_cut
{
	double			pos[6];
	void			*next;
}					t_cut;

typedef struct		s_tex
{
	char			*data;
	int				heigh;
	int				weigh;
	int				y_line;
	int				x_line;
}					t_tex;

typedef struct		s_spot
{
	char			*name;
	int				type;
	double			pos[6];
	int				c_s;
	void			*next;
}					t_spot;

typedef struct		s_obj
{
	char			*name;
	int				type;
	double			pos[6];
	double			size[3];
	double			eff[6];
	int				c_o;
	struct s_obj	*comp;
	t_vector		tri[3];
	t_vector		nor;
	int				text;
	t_cut			*cut;
	void			*next;
}					t_obj;

typedef struct		s_scene
{
	char			*name;
	char			nb;
	double			cam[6];
	double			amb[2];
	t_spot			*spot;
	t_obj			*obj;
	void			*next;
}					t_scene;

typedef struct		s_gen
{
	t_scene			*sc;
	char			*data;
	t_mlx			mlx;
	int				rep; //
	char			nb;
	double			view_angle[3]; // check with vincent
}					t_gen;

void				error(int i, char *str);
void				parse_scene(t_gen *s, char *argv);
void				raytracing(t_gen *s);
void				print_cam(t_scene *s, char **tp, double *cam, char c);
void				print_spot(t_scene *s, char **to_print, char **tmp);
void				print_cut(t_scene *s, char **to_print, t_cut *cut, char c);
void				print_col(char **to_print, int col, char *tmp);
void				print_amb(t_scene *s, char **to_print, int col, char *temp);
void				print_text(t_scene *s, char **to_print, int col);
void				print_type(t_scene *s, char **to_print, char type);
void				print_size_eff(t_scene *s, char **tp, double *size, char c);

#endif
