#include "raystruct.h"

void			scene_1_rt(t_mlx *m)
{
	itow(m, layer(m, 0, 0)->img, 0, 0);
	itow(m, layer(m, 1, 0)->img, 0, 0);
}
