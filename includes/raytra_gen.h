/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytra_gen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:12:41 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/08/12 06:26:23 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRA_GEN_H
# define RAYTRA_GEN_H

# include "libft.h"
# include "get_next_line.h"
# include <gui.h>

# include <stdio.h>			/* to del */
# include <math.h>

# define SPHERE 0x1
# define RECTANGLE 0x2
# define PLAN 0x4
# define CONE 0x8
# define CYLINDRE 0x10
# define COMPLEXE 0x20
# define TORUS 0x40
# define BOLOID 0x80
# define TRIANGLE 0x100

/*
**	BOOL
*/

# define SAVE 0x1

# define DEBUG 0


typedef struct		s_vector
{
	double				x;
	double				y;
	double				z;
}					t_vector;

typedef struct		s_spot
{
	double			pos[6];			/* spot position [0-2] x y z ; direction [3-5] x y z*/
	int				c_s;				/* color 0xRGB */
	void			*next;
}					t_spot;

typedef struct		s_obj
{
	char			*name;
	int				type;				/* cf MACRO */
	double			pos[6];				/* obj position [0-2] x y z ; direction [3-5] x y z*/
	double			size[3];			/* cf doc */
	double			eff[4];				/* eff[0] = transparence , [1] = reflexion, [2] = refraction, [3] == negatif */
	int				c_o;				/* color 0xRGB */
	struct s_obj	*comp;				/* pour les objets complexes */
	t_vector		tri[3];				/* pour les .obj */
	t_vector		nor;				/* pour les .obj */
	double			cut[6];				/* a voir comment faire */
	void			*next;
}					t_obj;

typedef struct		s_scene
{
	char			*name;
	char			nb;					/* numero de la scene */
	double			cam[6];				/*camera position [0-2] x y z ; direction [3-5] x y z*/
	int				amb[2];				/* ambiance ; amb[0] == RGB ; amb[1] == % intensité */
	t_spot			*spot;
	t_obj			*obj;
	void			*next;
}					t_scene;

typedef struct		s_gen 			/* structure generale */
{
	t_obj			*to_move;			/* Objet courant */	
	t_scene			*sc;				/* Liste des scenes chargees */	
	GdkPixbuf		*pixbuf;
	GtkWidget		*pwindow;			/* La fenetre LOL */
	GtkWidget		*pdrawarea;
	GtkWidget		*pscene_choosefile;
	GtkWidget		*pscene_current_scene;
	GtkWidget		*pscene_object_select;
	pthread_mutex_t	lock_draw;
	/* La ou on dessine pour les nuls */	
	int				rep;				/* pour des booleens (keycode MLX) */
	char			nb;					/* nombre de scene */
}					t_gen;

void				error(int i, char *str);
void				parse_scene(t_gen *s, char *argv);
void				raytracing(t_gen *s);

#endif