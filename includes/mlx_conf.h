#ifndef MLX_CONF_H
# define MLX_CONF_H

# include "mlx_conf_menu.h"
# include "mlx_conf_img.h"

# define WIN_TITLE "Awsome RT bitchhhh"

/*
** GESTION DU TEMPS D'ARRET DE LA BOUCLE SI RIEN N'EST A AFFICHER
** Cela évite de spam le processeur du PC pour RIEN
*/
# define USLEEP_TIME 20000
# define USLEEP_BOOL 1

/*
** CONF PROPRE A MLX
** SCENE_MAX: taille statiquement alloué pour stoquer les scene dans un tableau
** pareil pour SCENE_IMG_MAX concernant les images de chaque scenes
** LAYER_MAX est le nombre de layer t_img necessaire pour le projet
*/
# define SCENE_MAX 3
# define SCENE_IMG_MAX 50
# define LAYER_MAX 6

# define MENU_MAX 5
# define BTN_MARGIN 10
# define MENU_FADE_TEMPO 15

# define PATH_XPM "./resources/scene_img/"
# define PATH_SCENE "./scene/"

# define MENU_TEXT_COLOR 0xFFFFFF

# define TXT_SCENE_ADD_NAME "Nom de la nouvelle scene:"

# include "mlx_input.h"

#endif
