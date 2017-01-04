#include "raystruct.h"

static void		free_list(t_flst *flst, t_flst *destroy)
{
	if (!flst)
		return ;
	while (flst)
	{
		destroy = flst;
		flst = flst->n;
		ft_strdel(&destroy->path);
		destroy->n = NULL;
		destroy->p = NULL;
		ft_memdel((void **)&destroy);
	}
}

static void		build_list(t_mlx *m, t_flst *new, DIR *dir, struct dirent *f)
{
	int		len;

	if (!(dir = opendir(PATH_SCENE)))
		error(2, "Cant open scene dir.");
	while ((f = readdir(dir)))
	{
		if ((len = ft_strlen(f->d_name)) < 3 || f->d_name[len - 1] != 't'
		|| f->d_name[len - 2] != 'r' || f->d_name[len - 3] != '.')
			continue ;
		if (!(new = (t_flst *)ft_memalloc(sizeof(t_flst))))
			error(2, "malloc t_flst struct");
		new->path = ft_strdup(f->d_name);
		if (!m->flst && (m->flst = new) && (!(new->p = (t_flst *)NULL)))
				new->n = (t_flst *)NULL;
		else if ((m->flst->p = new)
		&& (new->n = m->flst)
		&& (!(new->p = NULL)))
			m->flst = new;
	}
	closedir(dir);
}

void			btn_load_menu(void *ptr)
{
	t_mlx	*m;

	m = ptr;
	free_list(m->flst, (t_flst *)NULL);
	m->flst = NULL;
	build_list(m, m->flst, NULL, NULL);

}
