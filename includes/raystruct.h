/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raystruct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:39:12 by vbauguen          #+#    #+#             */
/*   Updated: 2016/08/18 21:33:26 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYSTRUCT_H
# define RAYSTRUCT_H
# define W_Y 1050
# define W_X 1680
// # define W_Y 267
// # define W_X 420
# define WIN_NAME "RT"
# define PI 3.14159265359
# define TEXWIDTH 64
# define TEXHEIGHT 64

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

# define EPS 0.001

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# include "mlx.h"
# include "libft.h"
#include "raytra_gen.h"

typedef struct		s_ray
{
	t_vector 		start;
	t_vector 		dir;
	t_vector 		norm;
	t_obj			*obj;
	double			inter[2];
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

typedef struct		s_thread
{
	int				nb;
	int				lim[4];
	t_id			*t;
	t_gen			*s;	
}					t_thread;


typedef struct		s_second_degree
{
	double			discriminant;
	double			a;
	double			b;
	double			c;
	double			dist;
}					t_second_degree;

typedef struct		s_cylindre
{
	double			previous_value1;
	double			previous_value2;
	double			dot;
	double			dot2;
	t_vector		objetpos_raypos;
	t_vector		pos;
	t_vector		dir;
	double			limit_dist;
	t_vector		plan1_pos;
	t_vector		plan2_pos;
	t_vector		plan1_dir;
	t_vector		plan2_dir;
	t_second_degree second;
	double			inter_plan1;
	double			inter_plan2;
	double			dist_pos_inter1;
	double			dist_pos_inter2;
	double			dist_inter2_plan;
	double			dist_inter1_plan;
}					t_cylindre;


typedef struct		s_boloid
{
	double			m;
	double			previous_value1;
	double			previous_value2;
	t_vector		pos;
	t_vector		dir;
	t_vector		intersection;
	t_second_degree second;
	t_vector		x;
}					t_boloid;

typedef struct		s_ellipse
{
	double			previous_value1;
	double			previous_value2;
	t_vector		pos;
	t_vector		dir;
	t_vector		intersection;
	t_vector		newpos;
	t_second_degree second;
}					t_ellipse;

typedef struct		s_sphere
{
	t_vector		inter;
	t_second_degree	second;
	t_vector		pos;
}					t_sphere;

typedef struct		s_triangle
{
	double			t;
	double			d;
	double			u;
	double			v;
	double			near;
	t_obj			*tmp;
	t_vector 		new_norm;
	t_vector 		test;
	t_vector 		c0;
	t_vector 		c1;
	t_vector 		c2;
	t_vector 		c3;
}					t_triangle;

typedef struct		s_inter
{
	double inter1;
	double inter2;
}					t_inter;
typedef struct		s_complex
{
	double		t;
	t_obj		*tmp;
	t_obj		*temp;
	double		nearest[2];
	t_inter		i;
	t_vector	norm;
	double		new_nearest;
}					t_complex;

typedef struct		s_cone
{
	double			previous_value1;
	double			previous_value2;
	t_second_degree	second;
	double			k;
	t_vector		pos;
	t_vector		dir;
	t_vector		x;
	t_vector		inter_pos;
	t_vector		lambda;
	double			size_cone;
	double			dist_plan;
	t_vector		plan_pos;
	t_vector		plan_dir;
	t_vector		test1;
	t_vector		test2;
	double			dist_inter1;
	double			dist_inter2;
}					t_cone;


typedef struct		s_carre
{
	double	t_min;
	double	tmax;
	double	t;
	double	tymin;
	double	tymax;
	double	tzmin;
	double	tzmax;
	double	dist;
	t_vector hitpoint;
	t_vector rec_pos;
	t_vector calc;
}					t_carre;


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
int					diffuse(t_scene *sc, t_ray *r, t_obj *tmp, double nearest, int col);
int					reflexion(t_scene *sc, t_ray *r, double m, int col, int ret, double eff);

/*
**									vector_functions.c
*/

double 				vector_dot(t_vector v1, t_vector v2);
t_vector 			vector_add(t_vector v1, t_vector v2);
t_vector			vector_cross(t_vector v1, t_vector v2);
t_vector 			vectordivby_scalar(t_vector v, double scalar);
t_vector 			vector_sub(t_vector v1, t_vector v2);
t_vector 			vector_mult(t_vector v1, t_vector v2);
double 				vector_magnitude(t_vector v);
t_vector 			vector_normalize(t_vector v);
t_vector			vectormultby_scalar(t_vector v, double scalar);
t_vector 			new_vector(double x, double y, double z);
double 				vector_dist(t_vector v1, t_vector v2);
t_vector 			vector_dir(t_vector v1, t_vector v2);
t_vector 			get_hitpoint(t_vector start, t_vector dir, double dist);
t_vector			vector_rev(t_vector v);

/*
**									threads.c
*/

void				init_threads(t_thread *t, t_id *t_g, t_gen *s);

/*
**									shadow_max.c
*/

double				cast_shadow(t_obj *s, t_vector hitpoint, t_spot *spot, t_obj *object);

/*
**									write_scene.c
*/

void				print_scene(t_scene *s);


/*
**									matrice_rot.c
*/

t_vector			matricerot_x(t_vector v, double angle);
t_vector 			matricerot_y(t_vector v, double angle);
t_vector			matricerot_z(t_vector v, double angle);

/*
**									color_functions.c  
*/

void				mlx_image_put_pixel(t_id *g, int x, int y, int color);
void				color_composants(int color, double *ret);
int					colorfromrgb(double *tab);
void				color_normalize(double *tab, double *tmp_tab, double factor, int c);

/*
**									intersec_ray.c  
*/

double				intersectray_sphere(t_ray *r, t_obj *s, t_inter *i);
double				intersectray_plane(t_ray *r, t_obj *s, t_inter *i);
double	intersectray_cylindre(t_ray *r, t_obj *s, t_inter *i);

double		cyl_touch_one_plan2(t_ray *r, t_obj *s, t_cylindre *cyl, t_inter *i);
double		cyl_touch_one_plan(t_ray *r, t_obj *s, t_cylindre *cyl, t_inter *i);
double		cyl_touch_two_plan(t_ray *r, t_obj *s, t_cylindre *cyl, t_inter *i);
void		cyl_norm(t_ray *r, t_cylindre *cyl);
double	equa_sec(double a, double b, double discriminant, t_inter *i);
double cut_object(t_obj *obj, double dist, t_ray *r, char c);
double intersectray_cone(t_ray *r, t_obj *s, t_inter *i);


double 				intersectray_carre(t_ray *r, t_obj *s, t_inter *i);
double 				intersectray_complex(t_ray *r, t_obj *s, int *col);
double 				intersectray_boloid(t_ray *r, t_obj *s, t_inter *i);
double 				intersectray_triangle(t_ray *r, t_obj *s, t_inter *i);
double				intersectray_ellipse(t_ray *r, t_obj *s, t_inter *i);

/*
**									perlin.c  
*/

double				perlin(double x, double y, double z);

/*
**									ray_touch.c  
*/

double			lenray_type(t_ray *r, t_obj *s, t_inter *i, int *col);
double				lenray(t_scene *sc, t_ray *r);

/*
**									texture.c  
*/

int					texture_earth(double u, double v, char *str, void *mlx);
int					texture_fire(double u, double v, char *str, void *mlx);
int					texture_black(double u, double v, char *str, void *mlx);
int					texture_ice(double u, double v, char *str, void *mlx);

/*
**									palette_couleur
*/

unsigned char		change_col(unsigned char *col, double *nbr);
void				abstract(unsigned char *t, int rowstride, int index);
void				brightness(unsigned char *t, int rowstride, int index);
void				darkness(unsigned char *t, int rowstride, int index);
void				negative(unsigned char *t, int rowstride, int index);
void				sepia(unsigned char *t, int rowstride, int index);
void				technicolor(unsigned char *t, int rowstride, int index);
void				polaroid(unsigned char *t, int rowstride, int index);
void				bgr(unsigned char *t, int rowstride, int index);
void				kodachrome(unsigned char *t, int rowstride, int index);
void				browni(unsigned char *t, int rowstride, int index);
void				vintage(unsigned char *t, int rowstride, int index);
void				black_and_white(unsigned char *t, int rowstride, int index);
void				lsd(unsigned char *t, int rowstride, int index);
void				antialiasing(unsigned char *t, int rowstride, int index);

#endif
