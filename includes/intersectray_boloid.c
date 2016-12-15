#include "raystruct.h"

double intersectray_boloid(t_ray *r, t_obj *s, double *x1, double *y1)
{
		(void)x1;
	(void)y1;
	(void)r;
	(void)s;

	double discriminant;
	//double dot;
	//double dot2;
	double a;
	double b;
	double c;
	double m;
	double dist;
	double test1;
	double test2;
	t_vector para_pos;
	t_vector para_dir;
	t_vector x;
	// t_vector p_top;
	// t_vector p_bot;

	//size->1 == l'angle
	para_pos = new_vector(s->pos[0], s->pos[1],s->pos[2]);
	para_dir = vector_normalize(new_vector(s->pos[3], s->pos[4],s->pos[5]));
	x = vector_sub(r->start, para_pos);
	a = vector_dot(r->dir, r->dir) - vector_dot(r->dir, para_dir) * vector_dot(r->dir, para_dir);
	b = 2 * (vector_dot(r->dir, x) - vector_dot(r->dir, para_dir) * (vector_dot(x, para_dir) + 2 * s->size[0]));
	c = vector_dot(x, x) - vector_dot(x, para_dir) * (vector_dot(x, para_dir) + 4 * s->size[0]);

	discriminant = b * b - 4 * (a * c);
	// p_top = new_vector(s->pos[0] - angle, s->pos[1] - angle, s->pos[2] - s->size[1]);
	// p_bot = new_vector(s->pos[0] + s->size[1], s->pos[1] + s->size[1], s->pos[2] + s->size[1]);
	if (discriminant < 0)
		return (0);
	test1 = *x1;
	test2 = *y1;
	dist = equa_sec(a, b, discriminant, x1, y1, 0);
	if (dist < 0)
	{
		*x1 = test1;
		*y1 = test2;
		return (0);
	}
	// if (vector_dist(get_hitpoint(r->start, r->dir, dist), para_pos) > s->size[1])
	// {
	// 	if ((-b + sqrtf(discriminant)) / (2 * a) > dist)
	// 		dist = (-b + sqrtf(discriminant)) / (2 * a);
	// 	if ((-b - sqrtf(discriminant)) / (2 * a) > dist)
	// 		dist = (-b - sqrtf(discriminant)) / (2 * a);
	// 	if (dist <= 0 || vector_dist(get_hitpoint(r->start, r->dir, dist),
	// 	para_pos) > s->size[1])
	// 	{
	// 		*x1 = test1;
	// 		*y1 = test2;
	// 		return (0);
	// 	}
	// }
	t_vector intersection_pos;

	intersection_pos = get_hitpoint(r->start, r->dir, dist);
	x = vector_sub(intersection_pos, para_pos);// P - C
	m = vector_dot(r->dir, para_dir) * dist + vector_dot(x, para_dir);
//	k = vector_dot(x, para_dir);
	r->norm = vector_sub(x, vectormultby_scalar(para_dir, m + s->size[0]));// (P - C) - V ? 
	//r->norm = vector_sub(r->norm, vectormultby_scalar(cone_dir, tan(s->size[1]) * tan(s->size[1]) * k));
	r->norm = vector_normalize(r->norm);
	return dist;
}