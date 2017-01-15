#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

enum	e_menu {
	NONE,
	LOAD_FILE,
	LOAD_SCENE,
	LOAD_SCENE_ADD,
	LOAD_OBJECT,
	LOAD_SPOT,
	LOAD_CAMERA
};

enum	e_scene {
	INTRO,
	RT
};

enum	e_anim {
	STATIC,
	FADE_IN,
	FADE_OUT
};

enum	e_status {
	DISABLED,
	MENU,
	IMG,
	IMG_ANIM,
	OBJECT
};

/*
** structure lié au image qui sont des objet,
** pouvant etre désactivé, ou une simple image, un bouton ou l'état d'un bouton
** contient également les info pour détecter des clic dessus et le pointeur
** vers la fonction appelé en cas de clic
*/
typedef struct		s_img_mouse
{
	char			btn;
	void			(*action)(void *gen, void *mlx);
	int				top[2];
	int				bot[2];
	int				over_id;
	int				click_id;
}					t_img_mouse;

typedef struct		s_img_anim
{
	enum e_anim		id;
	int				tempo;
}					t_img_anim;

typedef struct		s_img
{
	enum e_status	status;
	enum e_menu		menu;
	void			*img;
	char			*str;
	int				*ptr;
	int				i;
	int				bpp;
	int				sl;
	int				end;
	int				width;
	int				heigh;
	int				fade;
	int				fade_max;
	int				fade_min;
	t_img_anim		anim;
	t_img_mouse		mouse;
	int				pos[2];
	int				set_alpha;
}					t_img;

/*
** contien les tables de touche enfoncé ou relanché
*/
typedef struct		s_input_mouse
{
	char			left;
	char			right;
	int				wheelup;
	int				wheeldown;
	int				over_x;
	int				over_y;
	int				release_x;
	int				release_y;
}					t_input_mouse;

typedef struct		s_input_key
{
	char			left;
	char			right;
	char			up;
	char			down;
	char			shift;
}					t_input_key;

typedef struct		s_input
{
	char			mode;
	t_input_key		key;
	t_input_mouse	mouse;
}					t_input;

# include "mlx_input.h"

/*
** pilote quel menu est dessiner a lecran
*/
typedef struct		s_menu
{
	char			draw;
	enum e_menu		id;
	enum e_menu		next;
	char			*new_scene;
	struct s_scene	*scene;
	struct s_scene	*spot;
	struct s_scene	*obj;
}					t_menu;

/*
** pour les liste de type fichier, spot, objet
*/
typedef struct		s_flst
{
	char			*path;
	char			*path_preview;
	struct s_scene	*scene;
	struct s_spot	*spot;
	struct s_obj	*obj;
	int				top[2];
	int				bot[2];
	int				id;
	int				over;
	t_img			preview;
	struct s_flst	*p;
	struct s_flst	*n;
}					t_flst;

/*
** lien vers toutes les donnée
*/
typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_menu			menu;
	t_flst			*flst;
	int				total_file;
	int				loading;
	t_input			input;
	char			loop;
	char			loopstop;
	enum e_scene	scene;
	char			img_isload[SCENE_MAX];
	t_img			scene_img[SCENE_MAX][SCENE_IMG_MAX];
	t_get			get[GET_APP_MAX];
	t_get			*get_focus;
	int				winx;
	int				winy;
}					t_mlx;


#endif
