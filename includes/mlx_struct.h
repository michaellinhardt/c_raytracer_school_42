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

enum	e_get_input_mode {
	DOUBLE,
	INT,
	NAME
};

enum	e_get_status {
	GET_STATUS,
	ENABLED,
	VALID,
	CANCEL,
	RESET,
	LOCKED
};

/*
** permet d'afficher une boite de dialogue pour récupérer des donné utilisateur
** le status défini si elle est utilsé dans la scene ou non et si verouillé
** le input_mode permet de controler les input autorisé pendant le focus
** NOTE: le focus
** pour savoir quel input est focus, on vérifie la valeur du pointeur dans t_mlx
** null = pas d'input focus, sinon c'est le pointeur vers le t_get en cours
** d'édition.
** NOTE: le control des touches de gestion
** clic pour select, entrer pour valider, del et supr pour editer rapidement
** les fleche pour déplacer i dans le pointeur
** les hook de touche appeleron les function qui travail sur
** t_mlx->input_focus
** NOTE: le control des touche de contenue
** les hook de touche vérifie si le pointeur t_mlx->input_focus
** contiens une adresse dans ce cas tout input suit des regle de verification
** propre au parametre input_mode. Les touches d'édition sont valable sur tout
** les mode, sur INT par exemple seul 0-9 sont pris en compte
** NOTE: les appel de fonction cancel, valid, reset
** entrer prends le contenue de data et le copie dans target apres une
** conversion effectué selon le input_mode
** NOTE: le control des data
** C'est la loop mlx à chaque nouveau tous qui manipule le contenue
**
*/
typedef struct					s_get
{
	enum e_get_status			g_s;
	enum e_get_input_mode		i_m;
	int							pos[2];
	int							top[2];
	int							bot[2];
	int							size_min;
	int							size_max;
	int							val_min;
	int							val_max;
	void						*target;
	void						*data;
	void						*tmp;
	int							i;
	int							j;
}								t_get;

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

/*
** pilote quel menu est dessiner a lecran
*/
typedef struct		s_menu
{
	char			draw;
	enum e_menu		id;
	enum e_menu		next;
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
	int				winx;
	int				winy;
}					t_mlx;


#endif
