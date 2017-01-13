#include "raystruct.h"

void			menu_draw_actif(t_mlx *m, t_img *img)
{
	if (m->menu.draw == -1 || m->loading != 0)
		return ;
	else if (m->menu.id == LOAD_FILE)
		img = &m->scene_img[1][ID_IMG_BTN_LOAD];
	else if (m->menu.id == LOAD_SCENE)
		img = &m->scene_img[1][ID_IMG_BTN_SCENE];
	else if (m->menu.id == LOAD_OBJECT)
		img = &m->scene_img[1][ID_IMG_BTN_OBJECT];
	else if (m->menu.id == LOAD_SPOT)
		img = &m->scene_img[1][ID_IMG_BTN_SPOT];
	else if (m->menu.id == LOAD_CAMERA)
		img = &m->scene_img[1][ID_IMG_BTN_CAMERA];
	m->scene_img[1][ID_IMG_BTN_SELECTED].pos[0] = img->pos[0] - 3;
	m->scene_img[1][ID_IMG_BTN_SELECTED].pos[1] = img->pos[1] - 3;
	img = &m->scene_img[1][ID_IMG_BTN_SELECTED];
	layer_add(m, layer(m, 1, 0), img);
}

void			scene_build(t_mlx *m, t_img *lay, t_img *img, int i)
{
	if (m->menu.draw == 1)
		layer(m, 1, 1);
	if (m->scene == RT && m->menu.draw == 1
	&& m->menu.id >= LOAD_FILE && m->menu.id <= LOAD_SPOT)
		menu_draw(m, m->flst, -1, -1);
	while (m->scene_img[m->scene][++i].img)
	{
		if (((img = &m->scene_img[m->scene][i])->status > MENU)
		|| (m->menu.draw == 1 && img->status == MENU
		&& (img->menu == NONE || img->menu == m->menu.id)))
			layer_add(m, lay, img);
	}
	menu_draw_actif(m, (t_img *)NULL);
}
