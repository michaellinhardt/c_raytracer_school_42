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

// double intersectray_cone(t_ray *r, t_obj *s, double *x1, double *y1)
// {
// 	(void)x1;
// 	(void)y1;
// 	(void)r;
// 	(void)s;

// 	double discriminant;
// 	double a;
// 	double b;
// 	double c;
// 	double k;
// 	double dist;
// 	t_vector cone_pos;
// 	t_vector cone_dir;
// 	t_vector x;
// 	double test1;
// 	double test2;

// 	cone_pos = new_vector(s->pos[0], s->pos[1],s->pos[2]);
// 	cone_dir = vector_normalize(new_vector(s->pos[3], s->pos[4],s->pos[5]));
// 	x = vector_sub(r->start, cone_pos);
// 	k = tan(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2 : s->size[1]) * (M_PI / 180) / 2);
// 	a = vector_dot(r->dir, r->dir) - (1 + k * k) * vector_dot(r->dir, cone_dir) * vector_dot(r->dir, cone_dir);
// 	b = 2 * (vector_dot(r->dir, x) - (1 + k * k) * vector_dot(r->dir, cone_dir) * vector_dot(x, cone_dir));
// 	c = vector_dot(x, x) - (1 + k * k) *  vector_dot(x, cone_dir) *  vector_dot(x, cone_dir);

// 	discriminant = b * b - 4.0 * (a * c);
// 	if (discriminant < 0)
// 		return (0);
// 	if (discriminant >= 0)
// 	{
// 		test1 = *x1;
// 		test2 = *y1;
// 		dist = equa_sec(a, b, discriminant, x1, y1, 0);
// 		if (dist < 0)
// 		{
// 			*x1 = test1;
// 			*y1 = test2;
// 			return (0);
// 		}
// 		double q;

// 		q = s->size[0] / cos(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2 : s->size[1]) * (M_PI / 180) / 2);
// 		if (vector_dist(get_hitpoint(r->start, r->dir, dist), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, dist), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
// 		{
// 			if ((-b + sqrtf(discriminant)) / (2 * a) > dist)
// 				dist = (-b + sqrtf(discriminant)) / (2 * a);
// 			if ((-b - sqrtf(discriminant)) / (2 * a) > dist)
// 				dist = (-b - sqrtf(discriminant)) / (2 * a);
// 			if ( dist <=  0 ||vector_dist(get_hitpoint(r->start, r->dir, dist), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, dist), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
// 			{
// 				*x1 = test1;
// 				*y1 = test2;
// 				return (0);
// 			}
// 		}
// 		if (vector_dist(get_hitpoint(r->start, r->dir, *x1), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, *x1), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])// || vector_dist(get_hitpoint(r->start, r->dir, *y1), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, *y1), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
// 		{	
// 			t_vector center_dir;
// 			t_vector center_pos;
// 			double t;
// 			center_dir.x = -cone_dir.x;
// 			center_dir.y = -cone_dir.y;
// 			center_dir.z = -cone_dir.z;
// 			center_pos = get_hitpoint(cone_pos, center_dir, s->size[0]);
// 			t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
// 				*y1 = *x1;
// 				*x1 = t;

// 				r->norm = center_dir;
// 				// r->norm.x = -center_dir.x;
// 				// r->norm.y = -center_dir.y;
// 				// r->norm.z = -center_dir.z;

// 				return (t);
// 		}
// 		if (vector_dist(get_hitpoint(r->start, r->dir, *y1), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, *y1), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])// || vector_dist(get_hitpoint(r->start, r->dir, *y1), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, *y1), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
// 		{	
// 			t_vector center_dir;
// 			t_vector center_pos;
// 			double t;
// 			center_dir.x = -cone_dir.x;
// 			center_dir.y = -cone_dir.y;
// 			center_dir.z = -cone_dir.z;
// 			center_pos = get_hitpoint(cone_pos, center_dir, s->size[0]);
// 			t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
// 			if (*x1 < 0 || *x1 > t)
// 			{
// 				*y1 = *x1;
// 				*x1 = t;
// 				r->norm = center_dir;
// 				// r->norm.x = -center_dir.x;
// 				// r->norm.y = -center_dir.y;
// 				// r->norm.z = -center_dir.z;

// 				return (t);
// 			}
// 		}

// 	 t_vector intersection_pos;
// 	 // cone_dir.x = -cone_dir.x;
// 	 // cone_dir.y = -cone_dir.y;
// 	 // cone_dir.z = -cone_dir.z;

// 	 intersection_pos = get_hitpoint(r->start, r->dir, dist);
// 	x = vector_sub(intersection_pos, cone_pos);// P - C
// 	k = vector_dot(x, cone_dir);
// 	r->norm = vector_sub(x, vectormultby_scalar(cone_dir, k));// (P - C) - V * k? 
// 	if (*x1 < 0)
// 	{
// 		r->norm.x = -r->norm.x;
// 		r->norm.y = -r->norm.y;
// 		r->norm.z = -r->norm.z;
// 	}
// 	vector_normalize(r->norm);
// 		t_vector lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
// 	r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir, vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
// 		return dist;
// 	}
// 	return (0);
// }

// t_vector ComputeNormal(t_vector inter, t_vector aabbCenter)
// {
//     t_vector normals[] = {
//        (t_vector){1,0,0},
//        (t_vector){0,1,0},
//        (t_vector){0,0,1}
//     };
//     const t_vector interRelative = vector_normalize(vector_sub(inter, aabbCenter));
//     const float xyCoef = interRelative.y / interRelative.x;
//     const float zyCoef = interRelative.y / interRelative.z;

//     const int coef = (xyCoef < 1 && -1 < xyCoef) ? 1 :
//                       (zyCoef > 1 || -1 > zyCoef ? 0 : 2);
//     normals[coef].x = (interRelative.x < 0) ? normals[coef].x : -normals[coef].x;
//     normals[coef].y = (interRelative.y < 0) ? normals[coef].y : -normals[coef].y;
//     normals[coef].z = (interRelative.z < 0) ? normals[coef].z : -normals[coef].z;
//     return normals[coef]; 
// }
