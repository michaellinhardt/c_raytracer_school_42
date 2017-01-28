#include "raystruct.h"

int			area(t_img *img, t_flst *elem, int x, int y)
{
	int		topx;
	int		topy;
	int		botx;
	int		boty;

	topx = (img) ? img->mouse.top[0] : elem->top[0];
	topy = (img) ? img->mouse.top[1] : elem->top[1];
	botx = (img) ? img->mouse.bot[0] : elem->bot[0];
	boty = (img) ? img->mouse.bot[1] : elem->bot[1];
	if (x >= topx && x <= botx && y >= topy && y <= boty)
		return (1);
	return (0);
}
