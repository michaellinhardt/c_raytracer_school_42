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

# define ID_IMG_MENU_CADRE 0
# define ID_IMG_MENU_CADRE_LIGHTNING 1
# define ID_IMG_MENU_CADRE_LOGO 2

# define ID_IMG_BTN_LOAD 3
# define ID_IMG_BTN_LOAD_OVER 4
# define ID_IMG_BTN_LOAD_CLICK 5
# define ID_IMG_BTN_SAVE 6
# define ID_IMG_BTN_SAVE_OVER 7
# define ID_IMG_BTN_SAVE_CLICK 8

# define BOT_BTN_X_DECALLAGE 1

# define ID_IMG_BTN_SCENE 9
# define ID_IMG_BTN_SCENE_OVER 10
# define ID_IMG_BTN_SCENE_CLICK 11
# define ID_IMG_BTN_OBJECT 12
# define ID_IMG_BTN_OBJECT_OVER 13
# define ID_IMG_BTN_OBJECT_CLICK 14
# define ID_IMG_BTN_SPOT 15
# define ID_IMG_BTN_SPOT_OVER 16
# define ID_IMG_BTN_SPOT_CLICK 17
# define ID_IMG_BTN_CAMERA 18
# define ID_IMG_BTN_CAMERA_OVER 19
# define ID_IMG_BTN_CAMERA_CLICK 20

# define ID_IMG_BTN_ARROW_RIGHT_OFF 21
# define ID_IMG_BTN_ARROW_RIGHT 22
# define ID_IMG_BTN_ARROW_RIGHT_OVER 23
# define ID_IMG_BTN_ARROW_RIGHT_CLICK 24

# define ID_IMG_BTN_ARROW_LEFT_OFF 25
# define ID_IMG_BTN_ARROW_LEFT 26
# define ID_IMG_BTN_ARROW_LEFT_OVER 27
# define ID_IMG_BTN_ARROW_LEFT_CLICK 28

# define ID_IMG_PREVIEW_NO_IMG 29
# define ID_IMG_PREVIEW 30
# define ID_IMG_PREVIEW_OVER 31
# define ID_IMG_PREVIEW_CLIC 32

# define ID_MAX_AUTO_INIT 32
# define ID_IMG_LOADING 33

# define ID_IMG_BTN_SCENE_OFF 34
# define ID_IMG_BTN_OBJECT_OFF 35
# define ID_IMG_BTN_SPOT_OFF 36
# define ID_IMG_BTN_CAMERA_OFF 37


# define MENU_LOAD_X_MAX 4
# define MENU_LOAD_Y_MAX 3
# define MENU_LOAD_START_X W_X * 0.10
# define MENU_LOAD_START_Y W_Y * 0.08
# define MENU_LOAD_END_X W_X * 0.90
# define MENU_LOAD_END_Y W_Y * 0.90

# define MENU_LOAD_SIZE_X MENU_LOAD_END_X - MENU_LOAD_START_X
# define MENU_LOAD_SIZE_Y MENU_LOAD_END_Y - MENU_LOAD_START_Y
# define MENU_LOAD_TEXT_MARGIN_X 5
# define MENU_LOAD_TEXT_MARGIN_Y 5
# define MENU_LOAD_PREVIEW_NAME_SIZE_MAX 18
# define MENU_LOAD_PREVIEW_PATH "./resources/menu_load_preview/"
# define MENU_LOAD_WAIT_BEFORE_LOAD 40

# define MENU_LOAD_MARGIN_X 20
# define MENU_LOAD_MARGIN_Y 20

#endif
