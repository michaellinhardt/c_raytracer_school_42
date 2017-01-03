#include "raystruct.h"

// static void		lay_fade_out(t_img *img, int x, int y)
// {
// 	img->fade -= 5;
// 	if (img->fade < 0)
// 		img->fade = 0;
// 	y = -1;
// 	while (++y < WIN_Y)
// 	{
// 		x = -1;
// 		while (++x < data()->mlx.winx)
// 			img->str[(y * data()->mlx.winx + x) * 4 + 3] = img->fade;
// 	}
// }
//
// static void		lay_fade(t_img *img, int x, int y)
// {
// 	img->fade += 5;
// 	if (img->fade > 255)
// 		img->fade = 255;
// 	y = -1;
// 	while (++y < WIN_Y)
// 	{
// 		x = -1;
// 		while (++x < data()->mlx.winx)
// 			img->str[(y * data()->mlx.winx + x) * 4 + 3] = img->fade;
// 	}
// }

void			scene_0_intro(t_gen *d, t_mlx *m)
{

	(void)d;
	(void)m;
	// t_img	*lay;
	//
	// lay = layer(2, 0);
	// if (lay->fade < 255 && m->scene_img[0][0].anim_id != FADE_OUT)
	// 	lay_fade(lay, -1, -1);
	// if (m->scene_img[0][0].anim_id == FADE_OUT)
	// 	lay_fade_out(lay, -1, -1);
	// if (lay->fade == 0)
	// 	m->scene++, error(1, "scene suivante");
	// scene_img_push(d, m, -1, (t_img *)NULL);
	// itow(m, layer(1, 0)->img, 0, 0);
	// itow(m, layer(0, 0)->img, 0, 0);
	// itow(m, layer(2, 0)->img, 0, 0);
}
