# include "h_raystruct.h"

	
double vectorDot(t_vector v1, t_vector v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; // retourne le cosinus de l'angle entre le v2 et le v1
}

t_vector vectorAdd(t_vector v1, t_vector v2)
{
	t_vector result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; // ajoute les composantes du vecteur 1 a celles du vecteur 2
	return result;
}

t_vector vectorDivByScalar(t_vector v, double scalar)
{
	t_vector result = {v.x/scalar, v.y / scalar, v.z / scalar }; // divise les composante du vecteur 1 par un nombre reel
	return result;

}

t_vector vectorCross(t_vector v1, t_vector v2)
{
	t_vector result = { v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y};
	return result;
}

t_vector vectorMultByScalar(t_vector v, double scalar)
{
	t_vector result = {v.x*scalar, v.y * scalar, v.z * scalar }; // multiplie les composante du vecteur 1 par un nombre reel
	return result;

}

t_vector vectorSub(t_vector v1, t_vector v2)
{
	t_vector result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; // soustrait les composantes du vecteur 2 a celles du vecteur 1
	return result;
}

t_vector vectorMult(t_vector v1, t_vector v2)
{
	t_vector result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z }; // multiplie entre elles les composantes des deux vecteurs passes en parametre
	return result;
}


double vectorMagnitude(t_vector v)
{
	return (sqrtf(vectorDot(v, v))); // renvoie la magnitude d'un vecteur ( = sa 'longueur' dans le repere orthonorme)
}

t_vector vectorNormalize(t_vector v)
{
	double norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vector result;
	if (norm)
	{
		result.x = v.x / norm;
		result.y = v.y / norm;
		result.z = v.z / norm;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return result; // renvoie les composantes normalisees d'un vecteur (qui ne depasseront donc par [-1;1])
}

t_vector newVector(double x, double y, double z)
{
	t_vector result;

	result.x = x;
	result.y = y;
	result.z = z;

	return (result); // cree un nouveau vecteur avec pour composante les 3 variables passees en parametre
}

double vectorDist(t_vector v1, t_vector v2)
{
	t_vector sub;

	sub = vectorSub(v1, v2);
	return (vectorMagnitude(sub)); // renvoie la distance entre le point v2 et le point v1

}

t_vector vectorDir(t_vector v1, t_vector v2) //Renvoie un vecteur direction qui va de v2 vers v1
{
	t_vector sub;

	sub = vectorSub(v1, v2);
	sub = vectorNormalize(sub);
	return (sub);	
}

t_vector getHitpoint(t_vector start, t_vector dir, double dist)
{
	t_vector hitpoint;

	hitpoint.x = start.x + dist * dir.x;
	hitpoint.y = start.y + dist * dir.y;
	hitpoint.z = start.z + dist * dir.z;
	return (hitpoint); // renvoie les coordonnes du point touche par le rayon qui pat de start, suivant dir et faisant dist de long. P = x0 + x*t
}


