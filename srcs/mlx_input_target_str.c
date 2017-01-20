#include "raystruct.h"

char		*input_target_to_str(t_get *g)
{
	if (g->mode == MODE_DOUBLE)
		return (ft_putfloat(*g->target.ptr_double
			, INPUT_MODE_DOUBLE_PRECISION));
	else if (g->mode == MODE_DOUBLE_BUT_INT)
		return (ft_itoa((int)*g->target.ptr_double));
	else if (g->mode == MODE_INT)
		return (ft_itoa(*g->target.ptr_int));
	else if (g->mode == MODE_HEXA)
		return (ft_itoa_base(*g->target.ptr_int, 16, 1));
	else if (g->mode == MODE_HEXA_TO_DOUBLE)
		return (ft_itoa_base(*g->target.ptr_double, 16, 1));
	else if (g->mode >= MODE_STRING && g->mode <= MODE_STRING_FILE)
		return (ft_strdup(*g->target.ptr_str));
	else
		return ((char *)NULL);
}
