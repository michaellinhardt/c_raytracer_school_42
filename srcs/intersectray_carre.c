#include "raystruct.h"

double intersectray_carre(t_ray *r, t_obj *s, t_inter *i)
{

	double t_min = (-s->size[0] / 2 - (r->start.x - s->pos[0])) / r->dir.x; 
    double tmax = (s->size[0] / 2 - (r->start.x - s->pos[0])) / r->dir.x; 
 	double t;
    if (t_min > tmax)
    { 
    	t = t_min;
    	t_min = tmax;
    	tmax = t;
 	}
    double tymin = (-s->size[1] / 2 - (r->start.y - s->pos[1])) / r->dir.y; 
    double tymax = (s->size[1] / 2 - (r->start.y - s->pos[1])) / r->dir.y; 
 	
    if (tymin > tymax)
    {
    	t = tymin;
    	tymin = tymax;
    	tymax = t;
    } 
    if ((t_min > tymax) || (tymin > tmax)) 
        return 0; 
 
    if (tymin > t_min) 
        t_min = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    double tzmin = (-s->size[2] / 2 - (r->start.z - s->pos[2])) / r->dir.z; 
    double tzmax = (s->size[2] / 2 - (r->start.z - s->pos[2])) / r->dir.z; 
 
    if (tzmin > tzmax)
	{
		t = tzmin;
		tzmin = tzmax;
		tzmax = t;
	}
    if ((t_min > tzmax) || (tzmin > tmax)) 
        return 0; 
 
    if (tzmin > t_min) 
		t_min = tzmin; 
 
    if (tzmax < tmax)
		tmax = tzmax;
	double dist;
	dist = (t_min < tmax) ? t_min : tmax;
	i->inter1 = dist;
	i->inter2 = (t_min > tmax) ? t_min : tmax;
	t_vector hitpoint = get_hitpoint(r->start, r->dir, dist);
	t_vector rec_pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	t_vector calc = vector_sub(hitpoint, rec_pos);
	r->norm = new_vector(0, 0, 0);

	if (calc.x >= s->size[0] / 2)
		r->norm.x = 1;
	else if (calc.x <= -s->size[0] / 2)
		r->norm.x = -1;
	if (calc.y >= s->size[1] / 2)
		r->norm.y = 1;
	else if (calc.y <= -s->size[1] / 2)
		r->norm.y = -1;
	if (calc.z >= s->size[2] / 2)
		r->norm.z = 1;
	else if (calc.z <= -s->size[2] / 2)
		r->norm.z = -1;
	if (fabs(calc.x) >= fabs(calc.y) && fabs(calc.z) >= fabs(calc.y))
		r->norm.y = 0;
	else if (fabs(calc.x) >= fabs(calc.z) && fabs(calc.z) <= fabs(calc.y))
		r->norm.z = 0;
	else
		r->norm.x = 0;
    return (dist); 
}