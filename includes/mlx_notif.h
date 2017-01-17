#ifndef MLX_NOTIF_H
# define MLX_NOTIF_H

# define NOTIF_PER_SCREEN 4
# define NOTIF_SIZE_CHAR_X 10
# define NOTIF_SIZE_CHAR_Y 8
# define NOTIF_PADDING 5

# define NOTIF_POS_RIGHT_X W_X - 20
# define NOTIF_POS_RIGHT_Y W_Y - 33 - NOTIF_SIZE_CHAR_Y

# define NOTIF_COLOR_NORMAL 0xFFFFFF
# define NOTIF_COLOR_WARNING 0x00FF00
# define NOTIF_COLOR_ERROR 0xFF0000

enum	e_notif {
	N_NORMAL,
	N_WARNING,
	N_ERROR
};

/*
** Notif struct
*/
typedef struct		s_notif
{
	int				id;
	char			*msg;
	unsigned		color;
	enum e_notif	type;
	t_img			bloc;
	struct s_notif	*next;
}					t_notif;

#endif
