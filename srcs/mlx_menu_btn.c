#include "raystruct.h"

static void	btn_switch(t_mlx *m, int boolean, int trueval, int falseval)
{
	if (boolean)
	{
		m->scene_img[1][trueval].status = MENU;
		m->scene_img[1][falseval].status = DISABLED;
	}
	else
	{
		m->scene_img[1][trueval].status = DISABLED;
		m->scene_img[1][falseval].status = MENU;
	}
}

void		scene_btn(t_gen *d, t_mlx *m, t_img *img)
{
	btn_switch(m, (!m->menu.scene || !m->menu.obj ? 1 : 0)
								, ID_IMG_BTN_OBJECT_OFF, ID_IMG_BTN_OBJECT);
	btn_switch(m, (!m->menu.scene || !m->menu.spot ? 1 : 0)
									, ID_IMG_BTN_SPOT_OFF, ID_IMG_BTN_SPOT);
	btn_switch(m, (!m->menu.scene ? 1 : 0)
								, ID_IMG_BTN_CAMERA_OFF, ID_IMG_BTN_CAMERA);
	(void)d;
	(void)m;
	(void)img;
}
