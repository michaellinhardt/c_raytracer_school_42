#include "raystruct.h"

static void		free_list(t_mlx *m, t_flst *flst, t_flst *destroy)
{
	if (!flst)
		return ;
	while (flst)
	{
		destroy = flst;
		flst = flst->n;
		ft_strdel(&destroy->path);
		ft_strdel(&destroy->path_preview);
		if (destroy->preview.img)
			mlx_destroy_image(m->mlx, destroy->preview.img);
		destroy->n = NULL;
		destroy->p = NULL;
		ft_memdel((void **)&destroy);
	}
}

static int		is_regular_file(const char *path)
{
	struct stat		path_stat;

	ft_bzero(&path_stat, sizeof(struct stat));
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

// static void		load_preview(t_mlx *m, t_flst *elem)
// {
// 	ft_printf("is_file %s: %d\n", elem->path, is_regular_file(elem->path));
// 	(void)m;
// 	(void)elem;
// }

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
		m->flst->path_preview = ft_strjoin(MENU_LOAD_PREVIEW_PATH, f->d_name);
		ft_printf("is file %s: %d\n", m->flst->path_preview, is_regular_file(m->flst->path_preview));
	}
	closedir(dir);
}

void			menu_load_btn_open(void *ptr)
{
	t_mlx	*m;
	t_flst	*lst;
	int		total;

	m = ptr;
	free_list(m, m->flst, (t_flst *)NULL);
	m->flst = NULL;
	build_list(m, m->flst, NULL, NULL);
	lst = m->flst;
	total = 0;
	while (++total && lst && (lst->id = total))
		lst = lst->n;
	m->total_file = total;
	m->menu.id = LOAD_FILE;
}
