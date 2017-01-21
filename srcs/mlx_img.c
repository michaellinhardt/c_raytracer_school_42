#include "raystruct.h"
#include <stdio.h>

char 	*file_to_char(char *path_file_to_load)
{
	static char buf[100000];
	int fd;
	int rd;

	fd = open(path_file_to_load, O_RDONLY);
	if (fd == -1)
		error(4, "L'ouverture du fichier de miniature a echoue\n");
	rd = read(fd, buf, 100000);
	if (rd == -1)
		error(4, "La copie du fichier de miniature a echoue\n");
	close(fd);
	return (buf);
}

void	char_to_file(char *min_data, char *file_path)
{
	int fd;

	fd = open(file_path, O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if (fd == -1)
		error(4, "La creation du fichier de miniature a echoue\n");
	write(fd, min_data, 100000);
	close(fd);
	// printf("La scene a ete ecrite\n");
}

void	pixel_to_char(t_gen *s, int color, int x, int y)
{
	int		*ptr;
	int		*minptr;

	minptr = (int *)s->downscaled;
	ptr = (int *)s->data;
	ptr[W_X * y + x] = color;
	x = x / 8.4;
	y = y / 8.4;
	minptr[200 * y + x] = color;


	// printf("minptr  =  [%d]\n", minptr[200 * y + x]);
	// printf("downscaled  =  [%d]\n", ((int *)s->downscaled)[200 * y + x]);
}

void	*mlx_new_img(t_mlx *m, t_img *img, int width, int heigh)
{
	img->width = width;
	img->heigh = heigh;
	if (!(img->img)
	&& !(img->img = mlx_new_image(m->mlx, img->width, img->heigh)))
		error(2, "mlx_new_image()");
	if (!(img->str))
	{
		if (!(img->str = mlx_get_data_addr(img->img
			, &img->bpp, &img->sl, &img->end)))
			error(2, "mlx_get_data_addr()");
		img->ptr = (int *)img->str;
	}
	return (img->img);
}

void	*mlx_xpmtostruct(t_mlx *m, t_img *img, char *file)
{
	if (!(img->img)
	&& !(img->img = mlx_xpm_file_to_image(m->mlx, file
												, &img->width, &img->heigh)))
		error(2, "mlx_xpm_file_to_image()");
	if (!(img->str))
	{
		if (!(img->str = mlx_get_data_addr(img->img
			, &img->bpp, &img->sl, &img->end)))
			error(2, "mlx_get_data_addr()");
		img->ptr = (int *)img->str;
	}
	return (img->img);
}

int		itow(t_mlx *m, void *img, int x, int y)
{
	if (!mlx_put_image_to_window(m->mlx, m->win, img, x, y))
		error(2, "mlx_put_image_to_window()");
	return (1);
}
