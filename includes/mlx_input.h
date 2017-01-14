#ifndef MLX_INPUT_H
# define MLX_INPUT_H

# define INPUT_COLOR_ENABLED 0xFF000000
# define INPUT_COLOR_DISABLED 0xFF000000

# define INPUT_COLOR_BORDER 0xFFFF0000

# define INPUT_SIZE_CHAR_Y 30
# define INPUT_SIZE_CHAR_X 15

# define INPUT_SIZE_BORDER 3

# define GET_APP_MAX 30

enum	e_get_inputmode {
	DOUBLE,
	INT,
	NAME
};

enum	e_get_status {
	GET_ENABLED,
	GET_DISABLED,
	GET_FOCUS
};

enum	e_get_action {
	GET_WAITING,
	GET_BACKSPACE,
	GET_SUPPR,
	GET_LEFT,
	GET_RIGHT,
	GET_VALID,
	GET_CANCEL,
	GET_RESET,
	GET_CHAR
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
	enum e_menu					menu;
	enum e_get_status			status;
	enum e_get_action			action;
	enum e_get_inputmode		mode;
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

#endif
