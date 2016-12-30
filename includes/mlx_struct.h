#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

enum	e_menu {
	NONE,
	SCENE,
	SPOT,
	OBJ,
	ETC
};

enum	e_scene {
	INTRO,
	RT
};

typedef struct		s_img
{
	char			name[255];
	void			*img;
	char			*str;
	int				*ptr;
	int				bpp;
	int				sl;
	int				end;
	int				width;
	int				heigh;
	int				fade;
	int				i;
	int				pos[2];
	int				top[2];
	int				bot[2];
}					t_img;

typedef struct		s_input
{
	char			mode;
	char			mleft;
	char			mright;
	char			left;
	char			right;
	char			up;
	char			down;
	char			shift;
	int				wheelup;
	int				wheeldown;
	int				mo_x;
	int				mo_y;
	int				mr_x;
	int				mr_y;
}					t_input;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_input			input;
	char			loop;
	char			loopstop;
	enum e_scene	scene;
	char			img_isload[SCENE_MAX];
	t_img			layer;
	t_img			scene_img[SCENE_MAX][SCENE_IMG_MAX];
	int				winx;
	int				winy;
}					t_mlx;

#endif
