/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:46:50 by vbauguen          #+#    #+#             */
/*   Updated: 2016/08/06 07:38:34 by vbauguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

double intersectRayCone(t_ray *r, t_obj *s, double *x1, double *y1)
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
	double k;
	double dist;
	t_vector cone_pos;
	t_vector cone_dir;
	t_vector x;
	// t_vector p_top;
	// t_vector p_bot;

	//size->1 == l'angle
	cone_pos = newVector(s->pos[0], s->pos[1],s->pos[2]);
	cone_dir = vectorNormalize(newVector(s->pos[3], s->pos[4],s->pos[5]));
	x = vectorSub(r->start, cone_pos);
	k = tan(((s->size[1] > 150) ? 150 : s->size[1]) * (M_PI / 180) / 2);
	a = vectorDot(r->dir, r->dir) - (1 + k * k) * vectorDot(r->dir, cone_dir) * vectorDot(r->dir, cone_dir);
	b = 2 * (vectorDot(r->dir, x) - (1 + k * k) * vectorDot(r->dir, cone_dir) * vectorDot(x, cone_dir));
	c = vectorDot(x, x) - (1 + k * k) *  vectorDot(x, cone_dir) *  vectorDot(x, cone_dir);

	discriminant = b * b - 4.0 * (a * c);
	// p_top = newVector(s->pos[0] - angle, s->pos[1] - angle, s->pos[2] - s->size[1]);
	// p_bot = newVector(s->pos[0] + s->size[1], s->pos[1] + s->size[1], s->pos[2] + s->size[1]);

	
	if (discriminant >= 0)
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
		if (vectorDist(getHitpoint(r->start, r->dir, dist), cone_pos) > s->size[0] || vectorDist(getHitpoint(r->start, r->dir, dist), getHitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
		{
			if ((-b + sqrtf(discriminant)) / (2 * a) > dist)
				dist = (-b + sqrtf(discriminant)) / (2 * a);
			if ((-b - sqrtf(discriminant)) / (2 * a) > dist)
				dist = (-b - sqrtf(discriminant)) / (2 * a);
			if (vectorDist(getHitpoint(r->start, r->dir, dist), cone_pos) > s->size[0] || vectorDist(getHitpoint(r->start, r->dir, dist), getHitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
				return (0);
		}
		
	t_vector intersection_pos;

	intersection_pos = getHitpoint(r->start, r->dir, dist);
	x = vectorSub(intersection_pos, cone_pos);// P - C
	k = vectorDot(x, cone_dir);
	r->norm = vectorSub(x, vectorMultByScalar(cone_dir, k));// (P - C) - V * k? 
		// r->norm.x = -r->norm.x;
		// r->norm.y = -r->norm.y;
		// r->norm.z = -r->norm.z;
	// r->norm = vectorSub(r->norm, vectorMultByScalar(cone_dir, tan(s->size[1]) * tan(s->size[1]) * k));
	vectorNormalize(r->norm);
		return dist;
	}
 		return 0;
 	/*******************************************************************************************************************************************/
	// (void)x1;
	// (void)y1;
	// (void)r;
	// (void)s;
	// 	double a;
	// double b;
	// double c;
	// double d;
	// double e;
	// t_vector torus_pos;
	// t_vector torus_dir;
	// t_vector x;

	// torus_pos = newVector(s->pos[0], s->pos[1],s->pos[2]);
	// torus_dir = vectorNormalize(newVector(s->pos[3], s->pos[4],s->pos[5]));
	// x = vectorSub(r->start, torus_pos);//X
	// a = vectorDot(r->dir, r->dir) * vectorDot(r->dir, r->dir);
	// b = 4 * vectorDot(r->dir, r->dir) * vectorDot(r->dir, x);
	// c = 4 * vectorDot(r->dir, r->dir) * vectorDot(r->dir, r->dir) + 2 * vectorDot(r->dir, r->dir) * vectorDot(x, x) - 2 * (s->size[0] * s->size[0] + s->size[1] * s->size[1]) * vectorDot(r->dir, r->dir) + 4 * s->size[0] * s->size[0] * vectorDot(r->dir, torus_dir) * vectorDot(r->dir, torus_dir);
	// d = 4 * vectorDot(r->dir, x) * vectorDot(x, x) - 4 * (s->size[0] * s->size[0] + s->size[1] * s->size[1]) * vectorDot(r->dir, x) + 8 * s->size[0] * s->size[0] * vectorDot(r->dir, torus_dir) * vectorDot(x, torus_dir);
	// e = vectorDot(x, x) * vectorDot(x, x) - 2 * (s->size[0] * s->size[0] + s->size[1] * s->size[1]) * vectorDot(x, x) + 4 * s->size[0] * s->size[0] * vectorDot(x, torus_dir) * vectorDot(x, torus_dir) + (s->size[0] * s->size[0] - s->size[1] * s->size[1]) * (s->size[0] * s->size[0] - s->size[1] * s->size[1]);
	// return (ferrari(a, b, c, d, e));
}

double intersectRayCylindre(t_ray *r, t_obj *s, double *x1, double *y1)
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
	// t_vector p_top;
	// t_vector p_bot;

	cyl_pos = newVector(s->pos[0], s->pos[1],s->pos[2]);
	cyl_dir = vectorNormalize(newVector(s->pos[3], s->pos[4],s->pos[5]));

	dot = vectorDot(r->dir, cyl_dir);
	tmp = vectorSub(r->start, cyl_pos);
	dot2 = vectorDot(tmp, cyl_dir);
	// dot2 = vectorDot(r->dir, cyl_dir);

	a = vectorDot(vectorSub(r->dir, vectorMultByScalar(cyl_dir, dot)), vectorSub(r->dir, vectorMultByScalar(cyl_dir, dot)));
	b = 2 * vectorDot(vectorSub(r->dir, vectorMultByScalar(cyl_dir, dot)), vectorSub(tmp, vectorMultByScalar(cyl_dir, dot2)));
	c = vectorDot(vectorSub(tmp, vectorMultByScalar(cyl_dir, dot2)), vectorSub(tmp, vectorMultByScalar(cyl_dir, dot2))) - s->size[0] * s->size[0];


	discriminant = b * b - 4 * (a * c);
	// p_top = newVector(s->pos[0] - s->size[1], s->pos[1] - s->size[1], s->pos[2] - s->size[1]);
	// p_bot = newVector(s->pos[0] + s->size[1], s->pos[1] + s->size[1], s->pos[2] + s->size[1]);

	if (discriminant >= 0)
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
		t_vector temp;
		t_vector tp;
		t_vector ab;
		t_vector proj;
		t_vector cyl_pos_dir = newVector(s->pos[0] + s->pos[3], s->pos[1] + s->pos[4], s->pos[2] + s->pos[5]);

		temp = vectorMultByScalar(r->dir, dist);
		temp = vectorAdd(temp, r->start);
		proj = vectorSub(cyl_pos_dir, temp);
		ab = vectorSub(cyl_pos, cyl_pos_dir);
		tp = vectorMultByScalar(ab, vectorDot(ab, proj) / vectorDot(ab, ab));
		tp = vectorAdd(tp, cyl_pos_dir);

		proj.x = tp.x;
		proj.y = tp.y;
		proj.z = tp.z;
		proj = vectorSub(cyl_pos, proj);
		r->norm = temp;
		proj = vectorAdd(proj, cyl_pos);
		r->norm = vectorNormalize(vectorSub(proj, r->norm));
		if (vectorDist(getHitpoint(r->start, r->dir, dist), cyl_pos) > s->size[1])
		{
			if (((-b + sqrtf(discriminant)) / (2 * a)) > dist)
				dist = ((-b + sqrtf(discriminant)) / (2 * a));
			if (((-b - sqrtf(discriminant)) / (2 * a)) > dist)
				dist = ((-b - sqrtf(discriminant)) / (2 * a));
			if (vectorDist(getHitpoint(r->start, r->dir, dist), cyl_pos) > s->size[1])
				return (0);
		}
		r->norm.x = -r->norm.x;
		r->norm.y = -r->norm.y;
		r->norm.z = -r->norm.z;
		r->norm = vectorNormalize(r->norm);
		return dist;
	}
 		return 0;

	
}

t_vector ComputeNormal(t_vector inter, t_vector aabbCenter)
{
    t_vector normals[] = { // A cube has 3 possible orientations
       (t_vector){1,0,0},
       (t_vector){0,1,0},
       (t_vector){0,0,1}
    };
    const t_vector interRelative = vectorNormalize(vectorSub(inter, aabbCenter));
    const float xyCoef = interRelative.y / interRelative.x;
    const float zyCoef = interRelative.y / interRelative.z;

    const int coef = (xyCoef < 1 && -1 < xyCoef) ? 1 :
                      (zyCoef > 1 || -1 > zyCoef ? 0 : 2);
    normals[coef].x = (interRelative.x < 0) ? normals[coef].x : -normals[coef].x;
    normals[coef].y = (interRelative.y < 0) ? normals[coef].y : -normals[coef].y;
    normals[coef].z = (interRelative.z < 0) ? normals[coef].z : -normals[coef].z;
    return normals[coef]; // The sign he is used to know direction of the normal
}

double intersectRayCarre(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)x1;
	(void)y1;
	double t_min = (-s->size[0] - (r->start.x - s->pos[0])) / r->dir.x; 
    double tmax = (s->size[0] - (r->start.x - s->pos[0])) / r->dir.x; 
 	double t;
    if (t_min > tmax)
    { 
    	t = t_min;
    	t_min = tmax;
    	tmax = t;
 	}
    double tymin = (-s->size[1] - (r->start.y - s->pos[1])) / r->dir.y; 
    double tymax = (s->size[1] - (r->start.y - s->pos[1])) / r->dir.y; 
 
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
 
    double tzmin = (-s->size[2] - (r->start.z - s->pos[2])) / r->dir.z; 
    double tzmax = (s->size[2] - (r->start.z - s->pos[2])) / r->dir.z; 
 
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
	

    r->norm = ComputeNormal(getHitpoint(r->start, r->dir, (t_min < tmax) ? t_min : tmax), newVector(s->pos[0], s->pos[1], s->pos[2]));
    return (t_min < tmax) ? t_min : tmax; 
}

double intersectRaySphere(t_ray *r, t_obj *s, double *x1, double *y1)
{

	(void)x1;
	(void)y1;

	double a, b, c, discriminant;
	double dist;

	t_vector newpos;
	newpos = newVector(r->start.x - s->pos[0], r->start.y - s->pos[1],r->start.z - s->pos[2]);

	a = vectorDot(r->dir, r->dir);
	b = 2 * vectorDot(r->dir, newpos);
	c = vectorDot(newpos, newpos) - s->size[0] * s->size[0];


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
		hitpoint = getHitpoint(r->start, r->dir, dist);

		r->norm = newVector((hitpoint.x - s->pos[0]) / s->size[0], 
			(hitpoint.y - s->pos[1]) / s->size[0],
			(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vectorNormalize(r->norm);
		if (s->cut[3] || s->cut[4] || s->cut[5])
		{
			t_vector hitpoint;
			t_vector plan;
			double t;
			t_vector l;
			t_vector p0_l0;
			t_vector n;

			hitpoint = getHitpoint(r->start, r->dir, dist);
			plan = newVector(s->pos[0] + s->cut[0], s->pos[1] + s->cut[1], s->pos[2] + s->cut[2]);
			n = newVector(s->cut[3], s->cut[4], s->cut[5]);
			l = vectorDir(plan, hitpoint);
			n = vectorNormalize(n);
			p0_l0 = vectorSub(plan, hitpoint);
		 	double denom = vectorDot(l, n); 
   			t = vectorDot(p0_l0, n) / denom ;
	
					
			if (t > 0.000001 && t < s->size[0])
			{
				dist = fabs((-b + sqrtf(discriminant)) / (2 * a));

				if ( fabs((-b - sqrtf(discriminant)) / (2 * a)) > fabs(dist))
				{
					dist = fabs((-b - sqrtf(discriminant)) / (2 * a));
				// r->norm = newVector(-(hitpoint.x - s->pos[0]) / s->size[0], 
			// -(hitpoint.y - s->pos[1]) / s->size[0],
			// -(hitpoint.z - s->pos[2]) / s->size[0]);
		// r->norm = vectorNormalize(r->norm);
				}
				hitpoint = getHitpoint(r->start, r->dir, dist);
				plan = newVector(s->pos[0] + s->cut[0], s->pos[1] + s->cut[1], s->pos[2] + s->cut[2]);
				// n = newVector(s->cut[3], s->cut[4], s->cut[5]);
				l = vectorDir(plan, hitpoint);
				// n = vectorNormalize(n);
				p0_l0 = vectorSub(plan, hitpoint);
			 	double denom = vectorDot(l, n); 
					t = vectorDot(p0_l0, n) / denom ;
				if (t > 0.001 && t < s->size[0])
				{
					return (0);
				}
				else
				{
			if (dist >= fabs((-b - sqrtf(discriminant)) / (2 * a)) && dist >= fabs((-b + sqrtf(discriminant)) / (2 * a)))
			{
				r->norm = newVector(-(hitpoint.x - s->pos[0]) / s->size[0], 
			-(hitpoint.y - s->pos[1]) / s->size[0],
			-(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vectorNormalize(r->norm);
			}
					hitpoint = getHitpoint(hitpoint, l, t); // getHitpoint(p0_l0, l, t) pour surface pleine
			

					return (vectorDist(r->start, hitpoint));
					
				}
			}
			if (dist >= fabs((-b - sqrtf(discriminant)) / (2 * a)) && dist >= fabs((-b + sqrtf(discriminant)) / (2 * a)))
			{
				r->norm = newVector(-(hitpoint.x - s->pos[0]) / s->size[0], 
			-(hitpoint.y - s->pos[1]) / s->size[0],
			-(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vectorNormalize(r->norm);
			}
		}
 		return dist;
	}
 	else
 		return 0;
}

double intersectRayComplex(t_ray *r, t_obj *p, double *x1, double *y1, int *col)
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
		if (!tmp->eff[3])
		{
			tmp = tmp->next;
			continue ;
		}
		tmp_near[0] = -1;
		tmp_near[1] = INT_MAX;
		if (tmp->type == SPHERE)
			t = intersectRaySphere(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == PLAN)
			t = intersectRayPlane(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == CYLINDRE)
			t = intersectRayCylindre(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == RECTANGLE)
			t = intersectRayCarre(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		if (t > 0.01 && tmp_near[0] != -1)
		{
			if (nearest[0] == -1 || (tmp_near[0] < nearest[0]) || tmp_near[1] > nearest[1])
			{
				if (nearest[0] == -1 || tmp_near[0] < nearest[0])
					nearest[0] = tmp_near[0];
				if (nearest[1] == INT_MAX || tmp_near[1] > nearest[1])
					nearest[1] = tmp_near[1];
				norm = r->norm;
			}
			t = 0;
		}
		tmp = tmp->next;
	}
	tmp = p->comp;
	temp = NULL;
	new_nearest = -1;
	while (tmp) //pour toute la liste d'objets
	{
		if (tmp->eff[3])
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == SPHERE)
			t = intersectRaySphere(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == PLAN)
			t = intersectRayPlane(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == CYLINDRE)
			t = intersectRayCylindre(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == RECTANGLE)
			t = intersectRayCarre(r, tmp, &tmp_near[0], &tmp_near[1]);
		if ((t < new_nearest && t > 0.00001)|| (new_nearest < 0 && t > 0.00001))
		{
			// si la distance actuelle calculee est plus petite que la precedente, on garde en memoire 
			//: la nouvelle plus courte intersection, l'objet concerne, et la normale du point touche
			if (t > nearest[0] && t < nearest[1] && nearest[0] > 0 /*&& nearest[1] < INT_MAX*/)
			{
				if (tmp_near[1] <= nearest[1] && tmp_near[0] >= nearest[0])
				{
					tmp = tmp->next;
					continue;
				}
				new_nearest = nearest[1];
				temp = tmp;
				r->obj = tmp;
				norm.x = -r->norm.x;
				norm.y = -r->norm.y;
				norm.z = -r->norm.z;
			}
			else
			{
				new_nearest = t;
				temp = tmp;
				r->obj = tmp;
				norm = r->norm;
			}
		}
		tmp = tmp->next; //objet suivant
	}
	if (new_nearest > 0.00001)
	{
		*col = temp->c_o;
		r->norm = norm;
	}
	return ((new_nearest != -1) ? new_nearest : 0); 
}

double intersectRayPlane(t_ray *r, t_obj *p, double *x1, double *y1)
{
	(void)x1;
	(void)y1;	
	double t;
	t_vector n;
	t_vector p0;

	p0 = newVector(p->pos[0], p->pos[1], p->pos[2]);
	n = vectorNormalize(newVector(p->pos[3], p->pos[4], p->pos[5]));
	t = (vectorDot(vectorSub(p0, r->start),n) / vectorDot(r->dir, n));
	if (t > 0.00001)
	{
		r->norm.x = n.x;
		r->norm.y = n.y;
		r->norm.z = n.z;
		// *x1 = t;
		// *y1 = *x1; 
		r->norm = vectorNormalize(r->norm);
		return (t);
	}
	return (0);
}
