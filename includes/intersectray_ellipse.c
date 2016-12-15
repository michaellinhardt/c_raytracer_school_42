#include "raystruct.h"

double intersectray_ellipse(t_ray *r, t_obj *s, double *x1, double *y1)
{
	double a;
	double b;
	double c;
	double test1;
	double test2;
	t_vector newpos;
	double dist;
	//double cmid;
	double discriminant;
	t_vector ellip_pos;
	t_vector ellip_dir;
	// t_vector tmp;


	test1 = *x1;
	test2 = *y1;
	newpos = new_vector(r->start.x - s->pos[0], r->start.y - s->pos[1],
	r->start.z - s->pos[2]);
	ellip_pos = new_vector(s->pos[0], s->pos[1], s->pos[2]);
	ellip_dir = vector_normalize(new_vector(s->pos[3], s->pos[4], s->pos[5]));
	// double dot = vector_dot(r->dir, ellip_dir);
	// tmp = vector_sub(r->dir, vectormultby_scalar(ellip_dir, dot));
	a = ((r->dir.x * r->dir.x) / (s->size[0] * s->size[0])) + ((r->dir.y * r->dir.y) / (s->size[1] * s->size[1])) + ((r->dir.z * r->dir.z) / (s->size[2] * s->size[2]));
	b = 2 * (((r->dir.x *newpos.x) / (s->size[0] * s->size[0])) + ((r->dir.y * newpos.y) / (s->size[1] * s->size[1])) + ((r->dir.z * newpos.z) / (s->size[2] * s->size[2])));
	c = ((newpos.x * newpos.x) / (s->size[0] * s->size[0])) + ((newpos.y * newpos.y) / (s->size[1] * s->size[1])) + ((newpos.z * newpos.z) / (s->size[2] * s->size[2])) - 1;
	discriminant = b * b - 4 * (a * c);
	test1 = *x1;
	test2 = *y1;
	if (discriminant < 0)
	{
		test1 = *x1;
		test2 = *y1;
		return (0);
	}
	dist = equa_sec(a, b, discriminant, x1, y1, 0);
	if (dist <= 0)
	{
		*x1 = test1;
		*y1 = test2;
		return (0);
	}
	t_vector intersection_pos;

	intersection_pos = get_hitpoint(r->start, r->dir, dist);
	r->norm = vector_sub(intersection_pos, ellip_pos);
	r->norm.x = 2 * r->norm.x / (s->size[0] * s->size[0]);
	r->norm.y = 2 * r->norm.y / (s->size[1] * s->size[1]);
	r->norm.z = 2 * r->norm.z / (s->size[2] * s->size[2]);
	r->norm = vector_normalize(r->norm);
	return (dist);
}