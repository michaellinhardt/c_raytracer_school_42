#include "raystruct.h"

static void		load_preview(t_mlx *m, t_flst *elem)
{
	struct stat		path_stat;

	ft_bzero(&path_stat, sizeof(struct stat));
	stat(elem->path_preview, &path_stat);
	if (S_ISREG(path_stat.st_mode) != 1)
		return ;
	mlx_xpmtostruct(m, &elem->preview, elem->path_preview);
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
		m->flst->path_preview = ft_strjoin(MENU_LOAD_PREVIEW_PATH, f->d_name);
		load_preview(m, m->flst);
	}
	closedir(dir);
}

void			menu_load_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_flst	*lst;
	int		total;

	m = mlx;
	menu_list_free(m, m->flst, (t_flst *)NULL);
	m->flst = NULL;
	build_list(m, m->flst, NULL, NULL);
	lst = m->flst;
	total = 0;
	while (++total && lst && (lst->id = total))
		lst = lst->n;
	m->total_file = total;
	m->menu.id = LOAD_FILE;
	(void)gen;
	(void)mlx;
}
