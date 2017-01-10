#ifndef MLX_CONF_H
# define MLX_CONF_H

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

/*
** Nombre de vignette par ligne et nombre de ligne
** modifiable a souhait, dans la mesure du raisonnable
*/
# define MENU_LOAD_X_MAX 4
# define MENU_LOAD_Y_MAX 3

/*
** Valeur pour calculer le positionnement du menu load
** .. ne pas trop jouer avec :)
*/

# define ID_IMG_MENU_CADRE 0
# define ID_IMG_MENU_CADRE_LIGHTNING 1
# define ID_IMG_MENU_CADRE_LOGO 2

# define ID_IMG_BTN_LOAD 3
# define ID_IMG_BTN_LOAD_OVER 4
# define ID_IMG_BTN_LOAD_CLICK 5
# define ID_IMG_BTN_SAVE 6
# define ID_IMG_BTN_SAVE_OVER 7
# define ID_IMG_BTN_SAVE_CLICK 8




# define ID_IMG_PREVIEW 10
# define ID_IMG_PREVIEW_OVER 11
# define ID_IMG_PREVIEW_CLIC 12

# define ID_IMG_LEFT_ARROW 4
# define ID_IMG_RIGHT_ARROW 4

# define ID_IMG_LOADING 13
# define MENU_LOAD_START_X W_X * 0.18
# define MENU_LOAD_START_Y W_Y * 0.07
# define MENU_LOAD_END_X W_X * 0.90
# define MENU_LOAD_END_Y W_Y * 0.90
# define MENU_LOAD_SIZE_X MENU_LOAD_END_X - MENU_LOAD_START_X
# define MENU_LOAD_SIZE_Y MENU_LOAD_END_Y - MENU_LOAD_START_Y
# define MENU_LOAD_TEXT_MARGIN_X 5
# define MENU_LOAD_TEXT_MARGIN_Y 5
# define MENU_LOAD_PREVIEW_NAME_SIZE_MAX 18
# define MENU_LOAD_PREVIEW_PATH "./resources/menu_load_preview/"
# define MENU_LOAD_PREVIEW_DECALLAGE_X 7
# define MENU_LOAD_PREVIEW_DECALLAGE_Y 7
# define MENU_LOAD_WAIT_BEFORE_LOAD 40

# define MENU_LOAD_MARGIN_X 20
# define MENU_LOAD_MARGIN_Y 20

#endif
