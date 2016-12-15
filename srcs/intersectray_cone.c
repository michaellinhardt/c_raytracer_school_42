#include "raystruct.h"

double intersectray_cone(t_ray *r, t_obj *s, t_inter *i)
{
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
	k = tan(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2 : s->size[1]) * (M_PI / 180) / 2);
	a = vector_dot(r->dir, r->dir) - (1 + k * k) * vector_dot(r->dir, cone_dir) * vector_dot(r->dir, cone_dir);
	b = 2 * (vector_dot(r->dir, x) - (1 + k * k) * vector_dot(r->dir, cone_dir) * vector_dot(x, cone_dir));
	c = vector_dot(x, x) - (1 + k * k) *  vector_dot(x, cone_dir) *  vector_dot(x, cone_dir);

	discriminant = b * b - 4.0 * (a * c);
	if (discriminant < 0)
		return (0);	
	test1 = i->inter1;
	test2 = i->inter2;
	dist = equa_sec(a, b, discriminant, i);
	if (i->inter1 < 0 && i->inter2 < 0)
	{
		i->inter1 = test1;
		i->inter2 = test2;
		return (0);
	}
	double q;
	q = s->size[0] / cos(((s->size[1] > 150) ? 150 * (M_PI / 180) / 2 : s->size[1]) * (M_PI / 180) / 2);
	
		t_vector tst1;
	t_vector tst2;

	tst1 = vector_normalize(vector_sub(get_hitpoint(r->start, r->dir, i->inter1), cone_pos));
	tst2 = vector_normalize(vector_sub(get_hitpoint(r->start, r->dir, i->inter2), cone_pos));
	// if (vector_dot(tst1, tst2) > 0)
	// {
	// 	i->inter1 = test1;
	// 	i->inter2 = test2;
	// 	return (0);
	// }
	if ((vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos) > q && (i->inter2 <= 0 || vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos) > q || vector_dot(tst2, cone_dir) > 0))|| (vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos) > q && (i->inter1 <= 0 || vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos) > q || vector_dot(tst1, cone_dir) > 0)))
	{
		// if ((vector_dist(get_hitpoint(r->start, r->dir, i->inter1), r->start) < 44 && vector_dist(get_hitpoint(r->start, r->dir, i->inter1), r->start) > 36) || (vector_dist(get_hitpoint(r->start, r->dir, i->inter2), r->start) < 44 && vector_dist(get_hitpoint(r->start, r->dir, i->inter2), r->start) > 36))
			// printf("c relou\n");
		i->inter1 = test1;
		i->inter2 = test2;
		return (0);
	}
	if (vector_dot(tst1, cone_dir) > 0 && vector_dot(tst2, cone_dir) > 0)
	{
		i->inter1 = test1;
		i->inter2 = test2;
		return (0);
	}
		//C CELUI LA

		// if (vector_dist(get_hitpoint(r->start, r->dir, dist), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, dist), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
		// {
		// 	if ((-b + sqrtf(discriminant)) / (2 * a) > dist)
		// 		dist = (-b + sqrtf(discriminant)) / (2 * a);
		// 	if ((-b - sqrtf(discriminant)) / (2 * a) > dist)
		// 		dist = (-b - sqrtf(discriminant)) / (2 * a);
		// 	if ( dist <=  0 ||vector_dist(get_hitpoint(r->start, r->dir, dist), cone_pos) > q || vector_dist(get_hitpoint(r->start, r->dir, dist), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
		// 	{
		// 		i->inter1= test1;
		// 		i->inter2 = test2;
		// 		return (0);
		// 	}
		// }

//	printf("lsls");
	t_vector intersection_pos;
	t_vector lambda;
	t_vector center_dir;
	t_vector center_pos;
	double t;
	if ((vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos) > q /*&& vector_dot(tst1, cone_pos) > 0*/) && (vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos) < q))// && vector_dot(tst2, cone_pos) < 0)
	{
		center_dir.x = -cone_dir.x;
		center_dir.y = -cone_dir.y;
		center_dir.z = -cone_dir.z;
		center_pos = get_hitpoint(cone_pos, center_dir, s->size[0]);
		t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
		// printf("pk\n");
		if (t > 0 && i->inter2 > t)
		{
			i->inter1 = t;
			r->norm = center_dir;
			// printf("moi\n");
			return (t);
		}
		intersection_pos = get_hitpoint(r->start, r->dir, i->inter2);
		lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
		vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
		// r->norm = vectormultby_scalar(r->norm, -1);
		//	printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);

		return (i->inter2);
	}
	if((vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos) < q /*&& vector_dot(tst2, cone_pos) > 0*/) && (vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos) > q))// && vector_dot(tst1, cone_pos) < 0)
	{
		// printf("lol\n");
		center_dir.x = -cone_dir.x;
		center_dir.y = -cone_dir.y;
		center_dir.z = -cone_dir.z;
		center_pos = get_hitpoint(cone_pos, center_dir, s->size[0]);
		t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
		if (t > 0 && i->inter1 > t)
		{
			i->inter2 = i->inter1;
			i->inter1 = t;
			r->norm = center_dir;
		// r->norm = vectormultby_scalar(r->norm, -1);
		//	printf("je comp\n");
			return (t);
		}
		intersection_pos = get_hitpoint(r->start, r->dir, i->inter1);
		lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
		vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
		// r->norm = vectormultby_scalar(r->norm, -1);
		// printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
		return (i->inter1);
	}
	if(vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos) < q && vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos) < q && vector_dot(tst1, tst2) < 0)// && vector_dot(tst1, cone_pos) < 0)
	{
		//printf("ll\n");
		center_dir.x = -cone_dir.x;
		center_dir.y = -cone_dir.y;
		center_dir.z = -cone_dir.z;
		center_pos = get_hitpoint(cone_pos, center_dir, s->size[0]);
		t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
		if (t > 0 && i->inter1 > t && i->inter2 > t)
		{
			i->inter2 = i->inter1;
			i->inter1 = t;
			r->norm = center_dir;
			//printf("toi\n");
			//printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
			return (t);
		}
		if (i->inter2 > i->inter1)
		{
			//printf("la\n");
			intersection_pos = get_hitpoint(r->start, r->dir, i->inter2);
			lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
			r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
			vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
		  //printf("i1 : %f , i2 : %f, q: %f\n", i->inter1, i->inter2, q);
			i->inter1 = i->inter2;
			i->inter2 = t;
			// printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
			// r->norm = vectormultby_scalar(r->norm, -1);
			return (i->inter1);
		}
		else
		{
			// printf("ici\n");
		 // printf("i1 : %f , i2 : %f, q: %f\n", vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos), vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos), q);
			intersection_pos = get_hitpoint(r->start, r->dir, i->inter1);
			lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
			r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
			vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
			i->inter2 = t;
			// r->norm = vectormultby_scalar(r->norm, -1);
			// printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
			
			return (i->inter1);
		}

	}
	// if((vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos) < q && vector_dot(tst1, cone_pos) < 0) && (vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos) < q && vector_dot(tst2, cone_pos) > 0) &&  vector_dist(get_hitpoint(r->start, r->dir, i->inter1), get_hitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])// && vector_dot(tst1, cone_pos) < 0)
	// {
	// 	printf("luuul\n");
	// 	center_dir.x = -cone_dir.x;
	// 	center_dir.y = -cone_dir.y;
	// 	center_dir.z = -cone_dir.z;
	// 	center_pos = get_hitpoint(cone_pos, center_dir, s->size[0]);
	// 	t = (vector_dot(vector_sub(center_pos, r->start),center_dir) / vector_dot(r->dir, center_dir));
	// 	if (t > 0 && i->inter1 > t && i->inter2 > t)
	// 	{
	// 		i->inter2 = i->inter1;
	// 		i->inter1 = t;
	// 		r->norm = center_dir;
	// 		printf("toi\n");
	// 		printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
	// 		return (t);
	// 	}
	// 	if (i->inter2 > i->inter1)
	// 	{
	// 		printf("la\n");
	// 		intersection_pos = get_hitpoint(r->start, r->dir, i->inter2);
	// 		lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
	// 		r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
	// 		vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
	// 	  //printf("i1 : %f , i2 : %f, q: %f\n", i->inter1, i->inter2, q);
	// 		i->inter1 = i->inter2;
	// 		i->inter2 = t;
	 //		printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
	// 		// r->norm = vectormultby_scalar(r->norm, -1);
	// 		return (i->inter1);
	// 	}
	// 	else
	// 	{
	// 		printf("ici\n");
	// 	 printf("i1 : %f , i2 : %f, q: %f\n", vector_dist(get_hitpoint(r->start, r->dir, i->inter1), cone_pos), vector_dist(get_hitpoint(r->start, r->dir, i->inter2), cone_pos), q);
	// 		intersection_pos = get_hitpoint(r->start, r->dir, i->inter1);
	// 		lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
	// 		r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
	// 		vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
	// 		i->inter2 = t;
	// 		// r->norm = vectormultby_scalar(r->norm, -1);
	// 		printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
			
	// 		return (i->inter1);
	// 	}

	// }
	if (i->inter1 > 0 && (i->inter2 < 0 || i->inter1 < i->inter2))
	{
	//	 printf("la");
		intersection_pos = get_hitpoint(r->start, r->dir, i->inter1);
		lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
		vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
		 // r->norm = vectormultby_scalar(r->norm, -1);
			printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
		
		return (i->inter1);
	}
	if (i->inter2 > 0 && (i->inter1 < 0 || i->inter2 < i->inter1))
	{
	//	 printf("iugyuguci\n");
		intersection_pos = get_hitpoint(r->start, r->dir, i->inter2);
		lambda = vector_normalize(vector_sub(cone_pos, intersection_pos));
		r->norm = vector_normalize(vector_sub(vectormultby_scalar(cone_dir,
		vector_dot(lambda, cone_dir) / vector_dot(cone_dir, cone_dir)),lambda));
		// r->norm = vectormultby_scalar(r->norm, -1);
			printf("norm : %f | %f | %f \n", r->norm.x, r->norm.y,r->norm.z);
		
		return (i->inter2);
	}
//	printf("poook\n");
	i->inter1 = test1;
	i->inter2 = test2;
	return (0);
}