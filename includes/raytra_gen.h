/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytra_gen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:12:41 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/12/18 07:46:45 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRA_GEN_H
# define RAYTRA_GEN_H

# include "libft.h"
# include "get_next_line.h"
# include <mlx.h>
# include <gtk/gtk.h>
# include <glib.h>
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
	t_obj			*to_move;
	t_scene			*sc;
	t_spot			*selected_spot;
	GdkPixbuf		*pixbuf;
	GtkWidget		*pwindow;
	GtkWidget		*pdrawarea;
	GtkWidget		*pscene_choosefile;
	GtkWidget		*pscene_current_scene;
	GtkWidget		*pscene_object_select;
	GtkWidget		*pscene_object_type;
	GtkWidget		*pscene_object_create;
	GtkWidget		*pscene_object_update;
	GtkWidget		*pscene_object_x;
	GtkWidget		*pscene_object_y;
	GtkWidget		*pscene_object_z;
	GtkWidget		*pscene_object_dir_x;
	GtkWidget		*pscene_object_dir_y;
	GtkWidget		*pscene_object_dir_z;
	GtkWidget		*pscene_object_size_x;
	GtkWidget		*pscene_object_size_y;
	GtkWidget		*pscene_object_size_z;
	GtkWidget		*pscene_object_color;
	GtkWidget		*pscene_object_name;
	GtkWidget		*pscene_object_negative;
	GtkWidget		*pscene_object_transparence;
	GtkWidget		*pscene_object_reflexion;
	GtkWidget		*pscene_object_refraction;
	GtkWidget		*pscene_spot_select;
	GtkWidget		*pscene_spot_x;
	GtkWidget		*pscene_spot_y;
	GtkWidget		*pscene_spot_z;
	GtkWidget		*pscene_spot_dir_x;
	GtkWidget		*pscene_spot_dir_y;
	GtkWidget		*pscene_spot_dir_z;
	GtkWidget		*pscene_spot_name;
	GtkWidget		*pscene_spot_color;
	GtkWidget		*pfilter_button_save;
	GtkWidget		*pfilter_button_apply;
	GtkWidget		*pfilter_choose_filter;
	char			*data;
	int				rep;
	char			nb;
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
