#include "raytra_gen.h"
#include "raystruct.h"

static void		prepare_data(t_get *g)
{
	char		*tmp;

	tmp = NULL;
	ft_bzero(&g->data, sizeof(g->data));
	ft_bzero(&g->tmp, sizeof(g->tmp));
	tmp = input_target_to_str(g);
	ft_memcpy(g->data, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
}

static void		set_focus(t_mlx *m, t_get *get, int tar, int i)
{
	m->getfocus = NULL;
	while (++i < GET_APP_MAX && (get = &m->get[i]))
		if (i != tar && get->status == GET_FOCUS)
			get->status = GET_ENABLED;
		else if (i == tar && get->status == GET_ENABLED && (m->getfocus = get))
		{
			get->status = GET_FOCUS;
			prepare_data(get);
		}
		else if (i == tar && get->status == GET_FOCUS && (m->getfocus = get))
		{
		}
}

static void		set_pos(t_get *get, int x, int max)
{
	int		start;
	int		mid;
	int		end;

	get->i = (x - INPUT_PADDING - get->box.pos[0]) / INPUT_SIZE_CHAR_X;
	start = get->i * INPUT_SIZE_CHAR_X;
	mid = start + (INPUT_SIZE_CHAR_X / 2);
	end = start + INPUT_SIZE_CHAR_X;
	if ((x - INPUT_PADDING - get->box.pos[0]) > mid)
		get->i++;
	if (get->i > max)
		get->i = max;
	scene_input_draw_cursor(NULL, NULL, NULL);
}

int				mouse_release_get(t_gen *d, int btn, int x, int y)
{
	t_get		*get;
	t_img		*img;
	int			i;
	int			is_one_focus;

	i = -1;
	is_one_focus = 0;
	while (++i < GET_APP_MAX)
	{
		if ((get = &d->mlx.get[i])->status == GET_FOCUS)
			is_one_focus++;
		if (area((img = &d->mlx.get[i].box), NULL, x, y)
		&& (btn == 1 || btn == 2) && d->mlx.menu.draw == 1
		&& get->menu > NONE && get->menu == d->mlx.menu.id)
		{
			if (btn == 1)
			{
				if (get->status != GET_FOCUS)
					set_focus(&d->mlx, (t_get *)NULL, i, -1);
				set_pos(get, x, (int)ft_strlen(get->data));
			}
			return (1);
		}
	}
	if (is_one_focus > 0)
		set_focus(&d->mlx, (t_get *)NULL, -1, -1);
	return (0);
}
