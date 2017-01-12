#include "raystruct.h"

int			scene_img_file(t_mlx *m, DIR *dir, struct dirent *f, char *path)
{
	char	*folder;
	char	*file;
	char	*tmp;

	folder = ft_strjoin(PATH_XPM, path);
	if (!(dir = opendir(folder)))
		error(3, "Cant open xpm sub dir.");
	while ((f = readdir(dir)))
	{
		if (!ft_isdigit(f->d_name[0]) || !ft_strstr(f->d_name, ".xpm"))
			continue ;
		file = ft_strjoin(folder, "/");
		tmp = file;
		file = ft_strjoin(tmp, f->d_name);
		m->scene_img[m->scene][ft_atoi(f->d_name)].img = mlx_xpmtostruct(m
			, &m->scene_img[m->scene][ft_atoi(f->d_name)], file);
		ft_strdel(&tmp);
		ft_strdel(&file);
	}
	closedir(dir);
	ft_strdel(&folder);
	return (1);
}

void		scene_img_folder(t_mlx *m, DIR *dir, struct dirent *f)
{
	if (!(dir = opendir(PATH_XPM)))
		error(2, "Open xpm dir..");
	while ((f = readdir(dir)))
	{
		if (!ft_isdigit(f->d_name[0]) || !ft_strstr(f->d_name, ".xpm"))
			continue ;
		else if (ft_atoi(f->d_name) == m->scene && scene_img_file(m
			, (DIR *)NULL, (struct dirent *)NULL, f->d_name))
			break ;
	}
	closedir(dir);
}

void		scene_img_load(t_gen *d, t_mlx *m)
{
	if (m->img_isload[m->scene] == 1)
		return ;
	scene_img_folder(m, (DIR *)NULL, (struct dirent *)NULL);
	scene_img_init(d, m);
	m->img_isload[m->scene] = 1;
}
