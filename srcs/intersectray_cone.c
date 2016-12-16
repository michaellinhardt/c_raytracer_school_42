#include "raystruct.h"

double intersectray_cone(t_ray *r, t_obj *s, t_inter *i)
{
	t_cone c;

	c.pos = new_vector(s->pos[0], s->pos[1],s->pos[2]);
	c.dir = vector_normalize(new_vector(s->pos[3], s->pos[4],s->pos[5]));
	c.x = vector_sub(r->start, c.pos);
	c.k = tan(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2 : s->size[1]) * (M_PI
	/ 180) / 2);
	c.second.a = vector_dot(r->dir, r->dir) - (1 + c.k * c.k) *
	vector_dot(r->dir, c.dir) * vector_dot(r->dir, c.dir);
	c.second.b = 2 * (vector_dot(r->dir, c.x) - (1 + c.k * c.k) *
	vector_dot(r->dir, c.dir) * vector_dot(c.x, c.dir));
	c.second.c = vector_dot(c.x, c.x) - (1 + c.k * c.k) * 
	vector_dot(c.x, c.dir) *  vector_dot(c.x, c.dir);
	c.second.discriminant = c.second.b * c.second.b - 4.0 *
	(c.second.a * c.second.c);
	if (c.second.discriminant < 0)
		return (0);	
	c.previous_value1 = i->inter1;
	c.previous_value2 = i->inter2;
	c.second.dist = equa_sec(c.second.a, c.second.b, c.second.discriminant, i);
	if (i->inter1 < 0 && i->inter2 < 0)
	{
		i->inter1 = c.previous_value1;
		i->inter2 = c.previous_value2;
		return (0);
	}
	c.size_cone = s->size[0] / cos(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2
	: s->size[1]) * (M_PI / 180) / 2);
	c.test1 = vector_normalize(vector_sub(get_hitpoint(r->start, r->dir,
	i->inter1), c.pos));
	c.test2 = vector_normalize(vector_sub(get_hitpoint(r->start, r->dir,
	i->inter2), c.pos));
	c.dist_inter1 = vector_dist(get_hitpoint(r->start, r->dir,
	i->inter1), c.pos);
	c.dist_inter1 = vector_dist(get_hitpoint(r->start, r->dir,
	i->inter2), c.pos);
	if ((c.dist_inter1 > c.size_cone && (i->inter2 <= 0 || c.dist_inter2 >
	c.size_cone || vector_dot(c.test2, c.dir) > 0)) || (c.dist_inter2 >
	c.size_cone && (i->inter1 <= 0 || c.dist_inter1 > c.size_cone ||
	vector_dot(c.test1, c.dir) > 0)))
	{
		i->inter1 = c.previous_value1;
		i->inter2 = c.previous_value2;
		return (0);
	}
	if (vector_dot(c.test1, c.dir) > 0 && vector_dot(c.test2, c.dir) > 0)
	{
		i->inter1 = c.previous_value1;
		i->inter2 = c.previous_value2;
		return (0);
	}
	if ((c.dist_inter1 > c.size_cone) && (c.dist_inter2 < c.size_cone))
	{
		c.plan_dir.x = -c.dir.x;
		c.plan_dir.y = -c.dir.y;
		c.plan_dir.z = -c.dir.z;
		c.plan_pos = get_hitpoint(c.pos, c.plan_dir, s->size[0]);
		c.dist_plan = (vector_dot(vector_sub(c.plan_pos, r->start),c.plan_dir) /
		vector_dot(r->dir, c.plan_dir));
		if (c.dist_plan > 0 && i->inter2 > c.dist_plan)
		{
			i->inter1 = c.dist_plan;
			r->norm = c.plan_dir;
			return (c.dist_plan);
		}
		c.inter_pos = get_hitpoint(r->start, r->dir, i->inter2);
		c.lambda = vector_normalize(vector_sub(c.pos, c.inter_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(c.dir,
		vector_dot(c.lambda, c.dir) / vector_dot(c.dir, c.dir)),c.lambda));
		return (i->inter2);
	}
	if((c.dist_inter1 < c.size_cone) && (c.dist_inter2 > c.size_cone))
	{
		c.plan_dir.x = -c.dir.x;
		c.plan_dir.y = -c.dir.y;
		c.plan_dir.z = -c.dir.z;
		c.plan_pos = get_hitpoint(c.pos, c.plan_dir, s->size[0]);
		c.dist_plan = (vector_dot(vector_sub(c.plan_pos, r->start),c.plan_dir) /
		vector_dot(r->dir, c.plan_dir));
		if (c.dist_plan > 0 && i->inter1 > c.dist_plan)
		{
			i->inter2 = i->inter1;
			i->inter1 = c.dist_plan;
			r->norm = c.plan_dir;
			return (c.dist_plan);
		}
		c.inter_pos = get_hitpoint(r->start, r->dir, i->inter1);
		c.lambda = vector_normalize(vector_sub(c.pos, c.inter_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(c.dir,
		vector_dot(c.lambda, c.dir) / vector_dot(c.dir, c.dir)),c.lambda));
		return (i->inter1);
	}
	if(c.dist_inter1 < c.size_cone && c.dist_inter2 < c.size_cone &&
	vector_dot(c.test1, c.test2) < 0)
	{
		c.plan_dir.x = -c.dir.x;
		c.plan_dir.y = -c.dir.y;
		c.plan_dir.z = -c.dir.z;
		c.plan_pos = get_hitpoint(c.pos, c.plan_dir, s->size[0]);
		c.dist_plan = (vector_dot(vector_sub(c.plan_pos, r->start),c.plan_dir)
		/ vector_dot(r->dir, c.plan_dir));
		if (c.dist_plan > 0 && i->inter1 > c.dist_plan &&
		i->inter2 > c.dist_plan)
		{
			i->inter2 = i->inter1;
			i->inter1 = c.dist_plan;
			r->norm = c.plan_dir;
			return (c.dist_plan);
		}
		if (i->inter2 > i->inter1)
		{
			c.inter_pos = get_hitpoint(r->start, r->dir, i->inter2);
			c.lambda = vector_normalize(vector_sub(c.pos, c.inter_pos));
			r->norm = vector_normalize(vector_sub(vectormultby_scalar(c.dir,
			vector_dot(c.lambda, c.dir) / vector_dot(c.dir, c.dir)),c.lambda));
			i->inter1 = i->inter2;
			i->inter2 = c.dist_plan;
			return (i->inter1);
		}
		else
		{
			c.inter_pos = get_hitpoint(r->start, r->dir, i->inter1);
			c.lambda = vector_normalize(vector_sub(c.pos, c.inter_pos));
			r->norm = vector_normalize(vector_sub(vectormultby_scalar(c.dir,
			vector_dot(c.lambda, c.dir) / vector_dot(c.dir, c.dir)),c.lambda));
			i->inter2 = c.dist_plan;
			return (i->inter1);
		}

	}
	if (i->inter1 > 0 && (i->inter2 < 0 || i->inter1 < i->inter2))
	{
		c.inter_pos = get_hitpoint(r->start, r->dir, i->inter1);
		c.lambda = vector_normalize(vector_sub(c.pos, c.inter_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(c.dir,
		vector_dot(c.lambda, c.dir) / vector_dot(c.dir, c.dir)),c.lambda));
		return (i->inter1);
	}
	if (i->inter2 > 0 && (i->inter1 < 0 || i->inter2 < i->inter1))
	{
		c.inter_pos = get_hitpoint(r->start, r->dir, i->inter2);
		c.lambda = vector_normalize(vector_sub(c.pos, c.inter_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(c.dir,
		vector_dot(c.lambda, c.dir) / vector_dot(c.dir, c.dir)),c.lambda));
		return (i->inter2);
	}
	i->inter1 = c.previous_value1;
	i->inter2 = c.previous_value2;
	return (0);
}