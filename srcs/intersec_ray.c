/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:46:50 by vbauguen          #+#    #+#             */
/*   Updated: 2016/08/19 04:48:32 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

double	equa_sec(double a, double b, double discriminant, double *x1, double *y1, double nbr)
{
	if (discriminant == 0)
	{
		*y1 = -1;
		*x1 = ((-b + sqrtf(discriminant)) / (2 * a))+ nbr;
		return (*x1); 
	}
	else
	{
		*x1 = ((-b + sqrtf(discriminant)) / (2 * a))+ nbr;
		*y1 = ((-b - sqrtf(discriminant)) / (2 * a)) + nbr;
		if (*y1 >= 0 && (*y1 < *x1 || *x1 < 0))
		{
			discriminant = *y1;
			*y1 = *x1;
			*x1 = discriminant;
		}
		if (*x1 >= 0)
			return (*x1);
		return (0);
	}
}

double cut_object(t_obj *obj, double dist, t_ray *r, char c)
{
	t_ray	tmp;
	t_cut	*cut;
	t_obj	new_plan;
	double	t;
	double	x1;
	double	y1;

	new_plan = *obj;
	new_plan.type = 0;
	x1 = 0;
	y1 = 0;
	new_plan.type ^= PLAN;
	cut = obj->cut;
	new_plan.cut = NULL;
	while (cut)
	{
		tmp = *r;
		ft_memcpy(new_plan.pos, cut->pos, sizeof(double) * 6);
		new_plan.pos[0] += obj->pos[0];
		new_plan.pos[1] += obj->pos[1];
		new_plan.pos[2] += obj->pos[2];
		t = intersectray_plane(&tmp, &new_plan, &x1, &y1);
		if (!c && t > EPS && t < dist)
			return (0);
		if (c && t > EPS && t > dist)
			return (0);
		cut = cut->next;
	}
	return (dist);
}
double	ferrari(double a, double b, double c, double d, double e)
{
	double p;
	double q;
	double r;
	double x[4];
	int i;
	//double discriminant;
	if (a != 0)
	{
		q = (8 * a * a * d + b * b * b - 4 * a * b * c) / (8 * a * a * a);
		p = (8 * a * c - 3 * b * b) / (8 * a * a);
		r = (16 * a * b * b * c - 64 * a * a * b * d - 3 * b * b * b * b + 256 * a * a * a * e) / 256 * a * a * a * a;
		if (q != 0)
		{
			x[0] = sqrtf((-p - sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			x[1] = -sqrtf((-p - sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			x[2] = sqrtf((-p + sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			x[3] = -sqrtf((-p + sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			i = 0;
			q = 0;
			while (i != 4)
			{
				if (x[i] >= 0 && (x[i] < q || q == 0))
					q = x[i];
				i++;
			}
			return (q);
		}
		else
		{
			return (0);
		}
	}
	return (0);
}

double intersectray_cone(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)x1;
	(void)y1;
	(void)r;
	(void)s;

	double discriminant;
	double a;
	double b;
	double c;
	double k;
	double dist;
	t_vector cone_pos;
	t_vector cone_dir;
	t_vector x;
	double test1;
	double test2;

	cone_pos = new_vector(s->pos[0], s->pos[1],s->pos[2]);
	cone_dir = vector_normalize(new_vector(s->pos[3], s->pos[4],s->pos[5]));
	x = vector_sub(r->start, cone_pos);
	k = tan(((s->size[1] > 150) ? 150 : s->size[1]) * (M_PI / 180) / 2);
	a = vector_dot(r->dir, r->dir) - (1 + k * k) * vector_dot(r->dir, cone_dir) * vector_dot(r->dir, cone_dir);
	b = 2 * (vector_dot(r->dir, x) - (1 + k * k) * vector_dot(r->dir, cone_dir) * vector_dot(x, cone_dir));
	c = vector_dot(x, x) - (1 + k * k) *  vector_dot(x, cone_dir) *  vector_dot(x, cone_dir);

	discriminant = b * b - 4.0 * (a * c);
	if (discriminant < 0)
		return (0);
	if (discriminant >= 0)
	{
		test1 = *x1;
		test2 = *y1;
		dist = equa_sec(a, b, discriminant, x1, y1, 0);
		if (dist < 0)
		{
			*x1 = test1;
			*y1 = test2;
			return (0);
		}
		if (vector_dist(get_hitpoint(r->start, r->dir, dist), cone_pos) > s->size[0] || vector_dist(get_hitpoint(r->start, r->dir, dist), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
		{
			if ((-b + sqrtf(discriminant)) / (2 * a) > dist)
				dist = (-b + sqrtf(discriminant)) / (2 * a);
			if ((-b - sqrtf(discriminant)) / (2 * a) > dist)
				dist = (-b - sqrtf(discriminant)) / (2 * a);
			if (vector_dist(get_hitpoint(r->start, r->dir, dist), cone_pos) > s->size[0] || vector_dist(get_hitpoint(r->start, r->dir, dist), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
			{
				*x1 = test1;
				*y1 = test2;
				return (0);
			}
			t_vector center_dir;
			t_vector center_pos;
			double t;
			center_dir = vector_rev(cone_dir);
			center_pos = get_hitpoint(cone_pos, cone_dir, s->size[0]);
			t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
			r->norm = center_dir;
			*x1 = t;
			*y1 = t;
			return (t);
		}
		
	 t_vector intersection_pos;
	 // cone_dir.x = -cone_dir.x;
	 // cone_dir.y = -cone_dir.y;
	 // cone_dir.z = -cone_dir.z;

	 intersection_pos = get_hitpoint(r->start, r->dir, dist);
	// x = vector_sub(intersection_pos, cone_pos);// P - C
	// k = vector_dot(x, cone_dir);
	// r->norm = vector_sub(x, vectormultby_scalar(cone_dir, k));// (P - C) - V * k? 
	// if (*x1 < 0)
	// {
	// 	r->norm.x = -r->norm.x;
	// 	r->norm.y = -r->norm.y;
	// 	r->norm.z = -r->norm.z;
	// }
	// vector_normalize(r->norm);
		t_vector lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
	r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir, vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
		return dist;
	}
	return (0);
}

double intersectray_boloid(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)r;
	(void)s;
	(void)x1;
	(void)y1;
	return (0);
}
double intersectray_torus(t_ray *r, t_obj *s, double *x1, double *y1)
{
	double a;
	double b;
	double c;
	double d;
	double e;
	double dist;
	t_vector torus_pos;
	t_vector torus_dir;
	t_vector intersection_pos;
	t_vector x;
	(void)x1;
	(void)y1;
	torus_pos = new_vector(s->pos[0], s->pos[1],s->pos[2]);
	torus_dir = vector_normalize(new_vector(s->pos[3], s->pos[4],s->pos[5]));
	x = vector_sub(r->start, torus_pos);
	
	a = pow(vector_dot(r->dir, r->dir), 2);
	b = 4 * vector_dot(r->dir, r->dir) * vector_dot(x, r->dir);
	c = 4 * pow(vector_dot(x, r->dir), 2) + 2 * vector_dot(r->dir, r->dir) * (vector_dot(x, x) - pow(s->size[1], 2) - pow(s->size[0], 2))
			+ 4 * pow(s->size[0], 2) * pow(vector_dot(r->dir, torus_dir), 2);
	d = 4 * vector_dot(x, r->dir) * (vector_dot(x, x)
			- pow(s->size[1], 2) - pow(s->size[0], 2)) + 8
			* pow(s->size[0], 2) *  vector_dot(x, torus_dir) * vector_dot(r->dir, torus_dir);
	e = pow((vector_dot(x, x) - pow(s->size[1], 2)
			- pow(s->size[0], 2)), 2) + 4 * pow(s->size[0], 2) * pow( vector_dot(x, torus_dir), 2)
			- 4 * pow(s->size[0], 2) * pow(s->size[1], 2);

	dist = ferrari(a, b, c, d, e);
	t_vector circ_pos;
	intersection_pos = get_hitpoint(r->start, r->dir, dist);
	circ_pos = get_hitpoint(torus_pos, torus_dir, s->size[0] - s->size[1]);
	r->norm = vector_normalize(vector_sub(intersection_pos, circ_pos));
	return (dist);
}

double intersectray_cylindre(t_ray *r, t_obj *s, double *x1, double *y1)
{
		(void)x1;
	(void)y1;
	(void)r;
	(void)s;

	double discriminant;
	double dot;
	double dot2;
	double a;
	double b;
	double c;
	double dist;
	t_vector cyl_pos;
	t_vector cyl_dir;
	t_vector tmp;

	cyl_pos = new_vector(s->pos[0], s->pos[1],s->pos[2]);
	cyl_dir = vector_normalize(new_vector(s->pos[3], s->pos[4],s->pos[5]));

	dot = vector_dot(r->dir, cyl_dir);
	tmp = vector_sub(r->start, cyl_pos);
	dot2 = vector_dot(tmp, cyl_dir);

	a = vector_dot(vector_sub(r->dir, vectormultby_scalar(cyl_dir, dot)), vector_sub(r->dir, vectormultby_scalar(cyl_dir, dot)));
	b = 2 * vector_dot(vector_sub(r->dir, vectormultby_scalar(cyl_dir, dot)), vector_sub(tmp, vectormultby_scalar(cyl_dir, dot2)));
	c = vector_dot(vector_sub(tmp, vectormultby_scalar(cyl_dir, dot2)), vector_sub(tmp, vectormultby_scalar(cyl_dir, dot2))) - s->size[0] * s->size[0];

	discriminant = b * b - 4 * (a * c);

	if (discriminant >= 0 && a)
	{
		dist = ((-b + sqrtf(discriminant)) / (2 * a));
		if ( ((-b - sqrtf(discriminant)) / (2 * a)) < (dist))
		{
			dist = ((-b - sqrtf(discriminant)) / (2 * a));
			if (dist < 0)
				return (0);
			*x1 = dist;
			*y1 = ((-b + sqrtf(discriminant)) / (2 * a));
		}
		else
		{
			if (dist < 0)
				return (0);
			*x1 = ((-b + sqrtf(discriminant)) / (2 * a));
			*y1 = ((-b - sqrtf(discriminant)) / (2 * a));
		}
		// if (vector_dist(get_hitpoint(r->start, r->dir, dist), cyl_pos) > s->size[1])
		// {
		// 	if (((-b + sqrtf(discriminant)) / (2 * a)) > dist)
		// 		dist = ((-b + sqrtf(discriminant)) / (2 * a));
		// 	if (((-b - sqrtf(discriminant)) / (2 * a)) > dist)
		// 		dist = ((-b - sqrtf(discriminant)) / (2 * a));
		// 	if (vector_dist(get_hitpoint(r->start, r->dir, dist), cyl_pos) > s->size[1])
		// 		return (0);
		// }
		t_vector   inter;
	    t_vector   proj;
	    t_vector   cyl_pos_dir;
	    t_vector   cyl_dir2;
	    double  dot3;
	    double  tmp;

	    cyl_pos_dir = vector_add(cyl_pos, cyl_dir);
	    cyl_dir2 = vector_sub(cyl_pos_dir, cyl_pos);
	    dot3 = vector_dot((cyl_dir2), (cyl_dir2));
	    inter = vectormultby_scalar(r->dir, dist);
	    inter = vector_add(inter, r->start);
	    proj = vector_sub(inter, cyl_pos_dir);
	    tmp = vector_dot((cyl_dir2), (proj)) / dot3;
		cyl_dir2 = vectormultby_scalar(cyl_dir2, tmp);
		cyl_dir2 = vector_add(cyl_dir2, cyl_pos_dir);
		proj = cyl_dir2;
		proj = vector_sub(proj, cyl_pos);
		r->norm = inter;
		proj = vector_add(cyl_pos, proj);
		r->norm = vector_sub(r->norm, proj);
		r->norm = vector_normalize(r->norm);
		if (s->cut)
		{
			if (!cut_object(s, dist, r, 0))
			{
				if (dist < ((-b + sqrtf(discriminant)) / (2 * a)))
					dist = ((-b + sqrtf(discriminant)) / (2 * a));
				else
					dist = ((-b - sqrtf(discriminant)) / (2 * a));
				// r->norm = vector_rev(r->norm);
				if (!cut_object(s, dist, r, 1))
					return (0);
			}
		}
		return dist;
	}
	return (0);
}

t_vector ComputeNormal(t_vector inter, t_vector aabbCenter)
{
    t_vector normals[] = {
       (t_vector){1,0,0},
       (t_vector){0,1,0},
       (t_vector){0,0,1}
    };
    const t_vector interRelative = vector_normalize(vector_sub(inter, aabbCenter));
    const float xyCoef = interRelative.y / interRelative.x;
    const float zyCoef = interRelative.y / interRelative.z;

    const int coef = (xyCoef < 1 && -1 < xyCoef) ? 1 :
                      (zyCoef > 1 || -1 > zyCoef ? 0 : 2);
    normals[coef].x = (interRelative.x < 0) ? normals[coef].x : -normals[coef].x;
    normals[coef].y = (interRelative.y < 0) ? normals[coef].y : -normals[coef].y;
    normals[coef].z = (interRelative.z < 0) ? normals[coef].z : -normals[coef].z;
    return normals[coef]; 
}

double intersectray_carre(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)x1;
	(void)y1;

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
	*x1 = dist;
	*y1 = (t_min > tmax) ? t_min : tmax;
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

double intersectray_sphere(t_ray *r, t_obj *s, double *x1, double *y1)
{

	(void)x1;
	(void)y1;

	double a, b, c, discriminant;
	double dist;

	t_vector newpos;
	newpos = new_vector(r->start.x - s->pos[0], r->start.y - s->pos[1],r->start.z - s->pos[2]);

	a = vector_dot(r->dir, r->dir);
	b = 2 * vector_dot(r->dir, newpos);
	c = vector_dot(newpos, newpos) - s->size[0] * s->size[0];


	discriminant = b * b - 4 * (a * c);

	dist = 0;
	if (discriminant >= 0)
	{
		dist = ((-b + sqrtf(discriminant)) / (2 * a));

		if (((-b + sqrtf(discriminant)) / (2 * a)) <= 0 || ((-b - sqrtf(discriminant)) / (2 * a)) <= 0)
			return (0);
		// dist = ((-b + sqrtf(discriminant)) / (2 * a));
		
		if ( ((-b - sqrtf(discriminant)) / (2 * a)) < (dist))
		{
			dist = ((-b - sqrtf(discriminant)) / (2 * a));
			*x1 = dist;
			*y1 = ((-b + sqrtf(discriminant)) / (2 * a));
		}
		else
		{
			*x1 = ((-b + sqrtf(discriminant)) / (2 * a));
			*y1 = ((-b - sqrtf(discriminant)) / (2 * a));
		}

		if ( ((-b - sqrtf(discriminant)) / (2 * a)) < (dist))
			dist = ((-b - sqrtf(discriminant)) / (2 * a));
		t_vector hitpoint;
		hitpoint = get_hitpoint(r->start, r->dir, dist);
		r->norm = new_vector((hitpoint.x - s->pos[0]) / s->size[0], 
			(hitpoint.y - s->pos[1]) / s->size[0],
			(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vector_normalize(r->norm);
		if (s->cut)
		{
			if (!cut_object(s, dist, r, 0))
			{
				if (dist < ((-b + sqrtf(discriminant)) / (2 * a)))
					dist = ((-b + sqrtf(discriminant)) / (2 * a));
				else
					dist = ((-b - sqrtf(discriminant)) / (2 * a));
				r->norm = vector_rev(r->norm);
				if (!cut_object(s, dist, r, 1))
					return (0);
			}
		}
 		return dist;
	}
 	else
 		return 0;
}



double intersectray_complex(t_ray *r, t_obj *p, double *x1, double *y1, int *col)
{
	double		t;
	t_obj		*tmp;
	t_obj		*temp;
	double		nearest[2];
	double		tmp_near[2];
	t_vector	norm;
	double		new_nearest;

	(void)x1;
	(void)y1;
	tmp = p->comp;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	while (tmp)
	{
		if (tmp->eff[3])
		{
			tmp_near[0] = -1;
			tmp_near[1] = INT_MAX;
			t = lenray_type(r, tmp, tmp_near, col);
			if (t > EPS && tmp_near[0] != -1)
				if (nearest[0] == -1 || (tmp_near[0] < nearest[0]) || tmp_near[1] > nearest[1])
				{
					if (nearest[0] == -1 || tmp_near[0] < nearest[0])
						nearest[0] = tmp_near[0];
					if (nearest[1] == INT_MAX || tmp_near[1] > nearest[1])
						nearest[1] = tmp_near[1];
					norm = r->norm;
				}
		}
		tmp = tmp->next;
	}
	tmp = p->comp;
	temp = NULL;
	new_nearest = -1;
	while (tmp) //pour toute la liste d'objets
	{
		if (!tmp->eff[3])
		{
			t = lenray_type(r, tmp, tmp_near, col);
			if ((t < new_nearest && t > EPS)|| (new_nearest < 0 && t > EPS))
			{
				if (t > nearest[0] && t < nearest[1] && nearest[0] > 0)
				{
					if (tmp_near[1] <= nearest[1] && tmp_near[0] >= nearest[0])
					{
						tmp = tmp->next;
						continue;
					}
					new_nearest = nearest[1];
					temp = tmp;
					r->obj = tmp;
					norm = vector_rev(norm);
				}
				else
				{
					new_nearest = t;
					temp = tmp;
					r->obj = tmp;
					norm = r->norm;
				}
			}
		}
		tmp = tmp->next;
	}
	if (new_nearest > EPS)
	{
		*col = temp->c_o;
		r->norm = norm;
	}
	return ((new_nearest != -1) ? new_nearest : 0); 
}

double intersectray_triangle(t_ray *r, t_obj *p, double *x1, double *y1)
{
	(void)y1;	
	double t;
	double d;
	double near;
	t_obj		*tmp;
	t_vector new;
	t_vector test;
	t_vector c0;
	t_vector c1;
	t_vector c2;
	t_vector c3;
	
	tmp = p->comp;
	near = INT_MAX;
	while (tmp)
	{
		c0 = vector_sub(tmp->tri[1], tmp->tri[0]);
		c1 = vector_sub(tmp->tri[2], tmp->tri[0]);
		test = vector_cross(r->dir, c1);
		d = vector_dot(c0, test);
		if (d > -0.00001 && d < 0.00001)
		{
			tmp = tmp->next;
			continue ;
		}
		t = 1.0 / d;
		c2 = vector_sub(r->start, tmp->tri[0]);
		double u = t * vector_dot(c2, test);
		if (u < 0.0 || u > 1.0)
		{
			tmp = tmp->next;
			continue ;	
		}
		c3 = vector_cross(c2, c0);
		double v = t * vector_dot(r->dir, c3);
		if (v < 0.0 || u + v > 1.0)
		{
			tmp = tmp->next;
			continue ;	
		}
		t = t * vector_dot(c1, c3);
		if (t > 0.01 && t < near)
		{
			new = tmp->nor;
			near = t;
		}
		tmp = tmp->next;
	}
	if (near > EPS && near < INT_MAX)
	{
		r->norm = new;
		*x1 = near;
		r->norm = vector_normalize(r->norm);
		return (near);
	}
	return (0);
}

double intersectray_plane(t_ray *r, t_obj *p, double *x1, double *y1)
{
	double		t;
	t_vector	n;
	t_vector	p0;

	p0 = new_vector(p->pos[0], p->pos[1], p->pos[2]);
	n = vector_normalize(new_vector(p->pos[3], p->pos[4], p->pos[5]));
	t = (vector_dot(vector_sub(p0, r->start),n) / vector_dot(r->dir, n));
	if (t > EPS)
	{
		r->norm = n;
		*x1 = t;
		*y1 = *x1; 
		r->norm = vector_normalize(r->norm);
		if (p->cut)
			return(cut_object(p, t, r, 0));
		return (t);
	}
	return (0);
}
