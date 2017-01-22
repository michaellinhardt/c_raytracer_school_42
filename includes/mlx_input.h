#ifndef MLX_INPUT_H
# define MLX_INPUT_H

# define INPUT_COLOR_ENABLED 0x00FFFFFF
# define INPUT_COLOR_DISABLED 0x00EEEEEE

# define INPUT_SIZE_CHAR_Y 30
# define INPUT_SIZE_CHAR_X 10

# define INPUT_BORDER_COLOR 0x00000000
# define INPUT_BORDER_COLOR_FOCUS 0x00FF0000
# define INPUT_BORDER_SIZE 2
# define INPUT_BORDER_FADE_SPEED 5

# define INPUT_NAME_COLOR 0xFFFFFF
# define INPUT_NAME_POS_X 7
# define INPUT_NAME_POS_Y -23

# define INPUT_TEXT_COLOR 0x000000
# define INPUT_TEXT_COLOR_FOCUS 0xFF0000
# define INPUT_TEXT_COLOR_DISABLED 0x10FF10

# define INPUT_CURSOR_COLOR 0x00000000
# define INPUT_CURSOR_FAME_TOTAL 30
# define INPUT_CURSOR_DISPLAY_UNDER 10
# define INPUT_CURSOR_MOVE_TEMPO 3
# define INPUT_CURSOR_DEL_TEMPO 5

# define INPUT_PADDING 10

# define INPUT_MODE_DOUBLE_PRECISION 6

# define GET_APP_MAX 30
# define GET_SIZE_MAX 255

# define NOTIF_INPUT_SAVE "save: "
# define NOTIF_INPUT_SIZE_MIN "minimum size for this input is: "

enum	e_get_inputmode {
	MODE_DOUBLE,
	MODE_DOUBLE_BUT_INT,
	MODE_INT,
	MODE_HEXA,
	MODE_HEXA_TO_DOUBLE,
	MODE_STRING,
	MODE_STRING_FILE
};

enum	e_get_status {
	GET_ENABLED,
	GET_DISABLED,
	GET_FOCUS
};

enum	e_get_action {
	GET_WAITING,
	GET_VALID,
	GET_RESET,
	GET_CHAR
};

typedef struct					s_get_target
{
	double						*ptr_double;
	int							*ptr_int;
	char						**ptr_str;
}								t_get_target;

typedef struct					s_get
{
	char						*name;
	enum e_menu					menu;
	enum e_get_status			status;
	enum e_get_action			action;
	enum e_get_inputmode		mode;
	void						(*draw)(void *gen, void *mlx, void *get);
	void						(*init)(void *gen, void *mlx, void *get);
	void						(*send)(void *gen, void *mlx, void *get);
	struct s_img				box;
	int							size_min;
	int							size_max;
	int							val_min;
	int							val_max;
	struct s_get_target			target;
	char						data[GET_SIZE_MAX];
	char						tmp[GET_SIZE_MAX];
	char						c;
	int							i;
	int							j;
}								t_get;

# define ID_INPUT_ADD_SCENE_NAME 0
# define ID_INPUT_MOD_SCENE_NAME 1
# define ID_INPUT_SCENE_AMBIANCE1 2
# define ID_INPUT_SCENE_AMBIANCE2 3

# define ID_INPUT_OBJECT_NAME 4
# define ID_INPUT_OBJECT_POS1 5
# define ID_INPUT_OBJECT_POS2 6
# define ID_INPUT_OBJECT_POS3 7
# define ID_INPUT_OBJECT_POS4 8
# define ID_INPUT_OBJECT_POS5 9
# define ID_INPUT_OBJECT_POS6 10

# define ID_INPUT_OBJECT_SIZE1 11
# define ID_INPUT_OBJECT_SIZE2 12
# define ID_INPUT_OBJECT_SIZE3 13

# define ID_INPUT_OBJECT_EFF1 14
# define ID_INPUT_OBJECT_EFF2 15
# define ID_INPUT_OBJECT_EFF3 16
# define ID_INPUT_OBJECT_EFF4 17
# define ID_INPUT_OBJECT_EFF5 18
# define ID_INPUT_OBJECT_EFF6 19

# define ID_INPUT_OBJECT_COLOR 20

# define ID_INPUT_ADD_OBJECT_NAME 21

# define ID_INPUT_SPOT_NAME 22
# define ID_INPUT_SPOT_COLOR 23
# define ID_INPUT_SPOT_POS1 24
# define ID_INPUT_SPOT_POS2 25
# define ID_INPUT_SPOT_POS3 26
# define ID_INPUT_SPOT_POS4 27
# define ID_INPUT_SPOT_POS5 28
# define ID_INPUT_SPOT_POS6 29

#endif
