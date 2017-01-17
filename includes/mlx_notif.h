#ifndef MLX_NOTIF_H
# define MLX_NOTIF_H

# define GET_SIZE_MAX 255

enum	e_notif {
	NORMAL,
	WARNING,
	BUG
};

/*
** Notif struct
*/
typedef struct		s_notif
{
	char			*msg;
	enum e_notif	type;
	t_img			bloc;
	struct s_notif	*next;
}					t_notif;

#endif
