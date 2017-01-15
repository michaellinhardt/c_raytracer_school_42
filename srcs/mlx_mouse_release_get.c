#include "raytra_gen.h"
#include "raystruct.h"

static void		set_focus(t_mlx *m, t_get *get, int target, int i)
{
	m->get_focus = NULL;
	while (++i < GET_APP_MAX && (get = &m->get[i]))
		if (i != target && get->status == GET_FOCUS)
			get->status = GET_ENABLED;
		else if (i == target && get->status == GET_ENABLED)
		{
			m->get_focus = get;
			get->status = GET_FOCUS;
		}
		else if (i == target && get->status == GET_ENABLED)
		{
			// on clic dans un input deja focus
		}
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
				set_focus(&d->mlx, (t_get *)NULL, i, -1);
			return (1);
		}
	}
	if (is_one_focus > 0)
		set_focus(&d->mlx, (t_get *)NULL, -1, -1);
	return (0);
}
