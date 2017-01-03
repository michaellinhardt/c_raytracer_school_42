#include "raystruct.h"

int			scene_img_file(t_dmlx *m, DIR *dir, struct dirent *f, char *path)
{
	char	*folder;
	char	*file;

	ft_printf("%!%sxpm/%s", &folder, data()->folder, path);
	if (!(dir = opendir(folder)))
		error(3, "Cant open xpm sub dir.");
	while ((f = readdir(dir)))
	{
		if (!ft_isdigit(f->d_name[0]) || !ft_strstr(f->d_name, ".xpm"))
			continue ;
		ft_printf("%!%s/%s", &file, folder, f->d_name);
		l1(1, f->d_name, "   loading xpm file");
		m->scene_img[m->scene][ft_atoi(f->d_name)].img = mlx_xpmtostruct(m
			, &m->scene_img[m->scene][ft_atoi(f->d_name)], file);
		ft_strdel(&file);
	}
	closedir(dir);
	ft_strdel(&folder);
	return (1);
}

void		scene_img_folder(t_mlx *m, DIR *dir, struct dirent *f)
{
	char	*folder;

	if (!(dir = opendir("./xpm")))
		error(3, "Cant open xpm dir.");
	while ((f = readdir(dir)))
	{
		if (!ft_strstr(f->d_name, ".xpm"))
			continue ;
		else if (ft_atoi(f->d_name) == m->scene && scene_img_file(m
			, (DIR *)NULL, (struct dirent *)NULL, f->d_name))
			break ;
	}
	closedir(dir);
}

void		scene_img(t_gen *d, t_mlx *m)
{
	(void)d;
	if (m->img_isload[m->scene] == 1)
		return ;
	scene_img_folder(m, (DIR *)NULL, (struct dirent *)NULL);
	scene_img_init(d, m);
	m->img_isload[m->scene] = 1;
}
