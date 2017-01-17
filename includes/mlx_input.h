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

enum	e_get_inputmode {
	MODE_DOUBLE,
	MODE_INT,
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
	char						*ptr_str;
}								t_get_target;

typedef struct					s_get
{
	enum e_menu					menu;
	enum e_get_status			status;
	enum e_get_action			action;
	enum e_get_inputmode		mode;
	void						(*send)(void *gen, void *mlx);
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

#endif
