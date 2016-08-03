/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_raystruct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:39:12 by vbauguen          #+#    #+#             */
/*   Updated: 2016/07/28 02:34:18 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define W_Y 1050
# define W_X 1680
# define WIN_NAME "RTv1"
# define PI 3.14159265359
# define KEYPRESS 2
# define KEYPRESSMASK (1L<<0)
# define POINTERMOTIOMMASK (1L<<6)
# define MOTIONNOTIFY 6
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define KEY_W keycode == 13
# define KEY_A keycode == 0
# define KEY_S keycode == 1
# define KEY_D keycode == 2
# define KEY_Q keycode == 12
# define KEY_E keycode == 14
# define KEY_T keycode == 17
# define KEY_UP keycode == 126
# define KEY_DOWN keycode == 125
# define KEY_LEFT keycode == 123
# define KEY_RIGHT keycode == 124
# define KEY_G keycode == 5
# define KEY_PGUP keycode == 116
# define KEY_PGDOWN keycode == 121
# define KEY_ESC keycode == 53

# define KEY_ONE 83
# define KEY_TWO 84
# define KEY_THR 85
# define KEY_FOU 86
# define KEY_FIV 87
# define KEY_SIX 88
# define KEY_SEV 89
# define KEY_EIG 91
# define KEY_NIN 92

# define MT 16
# define THE struct s_thread

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# include "mlx.h"
# include "libft.h"
#include "h_raytra_gen.h"


typedef struct		s_vector
{
	double				x;
	double				y;
	double				z;
}					t_vector;

typedef struct		s_ray
{
	t_vector 			start;
	t_vector 			dir;
	t_vector 			norm;
	t_obj				*obj;
	double				inter[2];
}					t_ray;

typedef struct		s_general
{
	char			c;
	double			bpp;
	int				bit_per_pixel;
	int				s_line;
	int				endian;
	char			*data;
	void			*img;
	void			*win;
	void			*mlx;
	int 			color;
	THE				*z;
}					t_id;

typedef struct	s_thread
{
	int			nb;
	int			lim[4];
	t_id		*t;
	t_gen		*s;	
}				t_thread;

/*
**									write_img.c
*/

void				print_bmp(char *str, t_id t, t_gen *s);

/*
**	key and mouse functions 		key_functions.c
**									mouse_functions.c
*/

int					quit_w(void);
int					mouse_functions(int button, int x, int y, t_gen *s);
int					release_key(int key, t_gen *s);
int					press_key(int key, t_gen *s);
int					key_reaction(int keycode);

/*
**									raytracing.c
*/
void				raytracing(t_gen *s);

/*
**									vector_functions.c
*/

double 				vectorDot(t_vector v1, t_vector v2);
t_vector 			vectorAdd(t_vector v1, t_vector v2);
t_vector 			vectorDivByScalar(t_vector v, double scalar);
t_vector 			vectorSub(t_vector v1, t_vector v2);
t_vector 			vectorMult(t_vector v1, t_vector v2);
double 				vectorMagnitude(t_vector v);
t_vector 			vectorNormalize(t_vector v);
t_vector			vectorMultByScalar(t_vector v, double scalar);
t_vector 			newVector(double x, double y, double z);
double 				vectorDist(t_vector v1, t_vector v2);
t_vector 			vectorDir(t_vector v1, t_vector v2);
t_vector 			getHitpoint(t_vector start, t_vector dir, double dist);

/*
**									threads.c
*/

void				init_threads(t_thread *t, t_id *t_g, t_gen *s);

/*
**									shadow_max.c
*/

double				cast_shadow(t_obj *s, t_vector hitpoint, t_spot *spot, t_obj *tmp);

/*
**									write_scene.c
*/

void				print_scene(t_gen *s);


/*
**									matrice_rot.c  (with doc)
*/

t_vector			MatricerotX(t_vector v, double angle);
t_vector 			MatricerotY(t_vector v, double angle);
t_vector			MatricerotZ(t_vector v, double angle);

/*
**									color_functions.c  
*/

void				mlx_image_put_pixel(t_id *g, int x, int y, int color);
void				color_composants(int color, double *ret);
int					colorfromrgb(double *tab);
void				colorNormalize(double *tab, double *tmp_tab, double factor, int c);

/*
**									intersec_ray.c  
*/

double				intersectRaySphere(t_ray *r, t_obj *s, double *x1, double *y1);
double				intersectRayPlane(t_ray *r, t_obj *s, double *x1, double *y1);
double 				intersectRayCylindre(t_ray *r, t_obj *s, double *x1, double *y1);
double 				intersectRayCarre(t_ray *r, t_obj *s, double *x1, double *y1);
double 				intersectRayComplex(t_ray *r, t_obj *s, double *x1, double *y1, int *col);

/*
**									perlin.c  
*/

double				perlin(double x, double y, double z);

/*
**									ray_touch.c  
*/

double				lenray(t_scene *sc, t_ray *r);

#endif
