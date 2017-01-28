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
# define SCENE_IMG_MAX 201
# define LAYER_MAX 6

# define MENU_MAX 5
# define BTN_MARGIN 10
# define MENU_FADE_TEMPO 15

# define PATH_XPM "./resources/scene_img/"
# define PATH_SCENE "./scene/"
# define PATH_NEW_SCENE "./resources/new_scene.rt"

# define MENU_TEXT_COLOR 0xFFFFFF

# define TXT_SCENE_ADD_NAME "New scene name:"
# define TXT_SCENE_ADD_NAME_DEFAUT "new_scene"

# define TXT_OBJECT_ADD_NAME "New object name:"
# define TXT_OBJECT_ADD_NAME_DEFAUT "new_object"

# define TXT_SPOT_ADD_NAME "New spot name:"
# define TXT_SPOT_ADD_NAME_DEFAUT "new_spot"

# define TXT_SCENE_MOD_NAME "Scene name:"
# define TXT_SCENE_MOD_AMB1 "Ambiance 1:"
# define TXT_SCENE_MOD_AMB2 "Ambiance 2:"

# define TXT_SCENE_DEL_VALID "Do you really want to delete this scene ?"
# define TXT_OBJECT_DEL_VALID "Do you really want to delete this object ?"
# define TXT_SPOT_DEL_VALID "Do you really want to delete this spot ?"

# define TXT_OBJECT_MOD_NAME "Object name:"
# define TXT_SPOT_MOD_NAME "Spot name:"

# define TXT_OBJECT_MOD_POS1 "Positon x:"
# define TXT_OBJECT_MOD_POS2 "Positon y:"
# define TXT_OBJECT_MOD_POS3 "Positon z:"
# define TXT_OBJECT_MOD_POS4 "Direction x:"
# define TXT_OBJECT_MOD_POS5 "Direction y:"
# define TXT_OBJECT_MOD_POS6 "Direction z:"

# define TXT_SPOT_MOD_POS1 "Positon x:"
# define TXT_SPOT_MOD_POS2 "Positon y:"
# define TXT_SPOT_MOD_POS3 "Positon z:"
# define TXT_SPOT_MOD_POS4 "Direction x:"
# define TXT_SPOT_MOD_POS5 "Direction y:"
# define TXT_SPOT_MOD_POS6 "Direction z:"

# define TXT_OBJECT_MOD_SIZE1 "Size 1:"
# define TXT_OBJECT_MOD_SIZE2 "Size 2:"
# define TXT_OBJECT_MOD_SIZE3 "Size 3:"

# define TXT_OBJECT_MOD_EFF1 "Effect 1:"
# define TXT_OBJECT_MOD_EFF2 "Effect 2:"
# define TXT_OBJECT_MOD_EFF3 "Effect 3:"
# define TXT_OBJECT_MOD_EFF4 "Effect 4:"
# define TXT_OBJECT_MOD_EFF5 "Effect 5:"
# define TXT_OBJECT_MOD_EFF6 "Effect 6:"

# define TXT_OBJECT_MOD_COLOR "Color:"
# define TXT_SPOT_MOD_COLOR "Color:"

# define TXT_OBJECT_MOD_TYPE "Actual type:"
# define TXT_OBJECT_TYPE_SPHERE "Sphere"
# define TXT_OBJECT_TYPE_RECTANGLE "Rectangle"
# define TXT_OBJECT_TYPE_PLAN "Plan"
# define TXT_OBJECT_TYPE_CONE "Cone"
# define TXT_OBJECT_TYPE_CYLINDRE "Cylindre"
# define TXT_OBJECT_TYPE_COMPLEXE "Complexe"
# define TXT_OBJECT_TYPE_BOLOID "Boloid"
# define TXT_OBJECT_TYPE_TRIANGLE "Triangle"
# define TXT_OBJECT_TYPE_ELLIPSE "Ellipse"

# define TXT_SPOT_MOD_TYPE "Actual type:"
# define TXT_SPOT_TYPE_DIIR "Directionnal"
# define TXT_SPOT_TYPE_POINT "Point..ctuel?"

# define TXT_CAMERA_MOD_TITLE "Edit camera position and direction:"
# define TXT_CAMERA_MOD_CAM1 "Position x:"
# define TXT_CAMERA_MOD_CAM2 "Position y:"
# define TXT_CAMERA_MOD_CAM3 "Position z:"
# define TXT_CAMERA_MOD_CAM4 "Direction x:"
# define TXT_CAMERA_MOD_CAM5 "Direction y:"
# define TXT_CAMERA_MOD_CAM6 "Direction z:"

#endif
