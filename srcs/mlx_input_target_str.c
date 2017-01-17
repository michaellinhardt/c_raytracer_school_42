#include "raystruct.h"

char		*input_target_to_str(t_get *g)
{
	if (g->mode == MODE_DOUBLE)
		return (ft_putfloat(**g->target.ptr_double
			, INPUT_MODE_DOUBLE_PRECISION));
	else if (g->mode == MODE_INT)
		return (ft_itoa(**g->target.ptr_int));
	else if (g->mode >= MODE_STRING && g->mode <= MODE_STRING_FILE)
		return (ft_strdup(*g->target.ptr_str));
	else
		return ((char *)NULL);
}