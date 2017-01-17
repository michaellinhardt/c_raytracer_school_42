#include "raytra_gen.h"
#include "raystruct.h"

static void		notif_free(t_mlx *m, t_notif *destroy)
{
	ft_strdel(&destroy->msg);
	destroy->next = NULL;
	ft_memdel((void **)&destroy);
	(void)m;
}

void			scene_text_notif(t_mlx *m, t_notif *lst)
{
	while (lst)
	{
		mlx_string_put(m->mlx, m->win, lst->bloc.pos[0] + NOTIF_PADDING
		, lst->bloc.pos[1], 0xFFFFFFFF, lst->msg);
		lst = lst->next;
	}
}

static void		notif_draw_pos(t_mlx *m, t_notif *lst, int pos)
{
	lst->bloc.pos[0] = NOTIF_POS_RIGHT_X - lst->bloc.width;
	lst->bloc.pos[1] = NOTIF_POS_RIGHT_Y - (lst->bloc.heigh * pos);
	(void)m;
}

void			notif_draw(t_mlx *m, t_notif *lst, t_notif *next)
{
	int			i;
	t_notif		*prev;

	prev = NULL;
	if (!m->notif)
		return ;
	i = -1;
	while (lst)
	{
		next = lst->next;
		if (++i < NOTIF_PER_SCREEN)
			notif_draw_pos(m, lst, i);
		else
		{
			if (!lst->next)
				notif_free(m, lst);
			if (prev)
				prev->next = NULL;
		}
		prev = lst;
		lst = next;
	}
}

void			notif(t_mlx *m, enum e_notif type, char *msg)
{
	t_notif		*n;
	static int	id = -1;

	if (!(n = (t_notif *)ft_memalloc((sizeof(t_notif)))))
		error(2, "ft_memalloc()");
	n->id = ++id;
	n->msg = ft_strdup(msg);
	n->type = type;
	n->bloc.fade = 0;
	n->bloc.width = ((int)ft_strlen(msg) * NOTIF_SIZE_CHAR_X)
	+ (NOTIF_PADDING * 2);
	n->bloc.heigh = NOTIF_SIZE_CHAR_Y + (NOTIF_PADDING * 2);
	n->next = m->notif;
	m->notif = n;
	if (type == N_NORMAL)
		n->color = NOTIF_COLOR_NORMAL;
	else if (type == N_WARNING)
		n->color = NOTIF_COLOR_WARNING;
	else if (type == N_ERROR)
		n->color = NOTIF_COLOR_ERROR;
}
