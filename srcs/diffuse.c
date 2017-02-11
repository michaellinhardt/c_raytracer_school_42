/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:39:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/11 23:14:22 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raystruct.h"

static void		diffuse_shadow_specular_end(t_color *c,
	t_ray *r, double *speculaire, double *obj_dotn)
{
	// si dot_light_norm est pas entre 1 et 90 on le passe a 0
	c->dot_light_norm = (c->dot_light_norm > 0 && c->dot_light_norm <= 90)
	? c->dot_light_norm : 0;
	// la mirroire de la lumiere et de la reflexion, voir wiki
	c->mirror_vec_light = vector_normalize(vector_sub(vectormultby_scalar(
	r->norm, 2 * vector_dot(r->norm, c->vec_obj_light)), c->vec_obj_light));
	// calcule le dot product entre la direction du spot et de la norm de lobjet
	*obj_dotn = vector_dot(r->norm, c->vec_obj_light);
	// passe la couleur du spot a 0 si le dot.p precedent nest pas entre 1 et 90
	c->i_l[c->i] = (*obj_dotn > 0 && *obj_dotn <= 90) ? c->i_l[c->i] : 0;
	// calcule le dot.p speculaire (entre vecteur lumiere et veteur camera)
	*speculaire = vector_dot(c->mirror_vec_light, c->vec_obj_eye);
	// annule le coef speculaire si besoin
	*speculaire = (*speculaire > 0 && *speculaire <= 90) ? *speculaire : 0;
	if (c->spot->type & DIIR)
		speculaire = 0;
}

static double	diffuse_shadow_specular(t_ray *r, t_color *c, t_scene *sc,
t_obj *tmp)
{
	double speculaire;
	double obj_dotn;
	double shad;

	speculaire = 1;
	// position du spot pour determiner plus tard la direction
	c->spot_pos = new_vector(c->spot->pos[0], c->spot->pos[1],
	c->spot->pos[2]);
	// couleur du spot pour le calcule final
	color_composants(c->spot->c_s, c->i_l);
	// calcule la direction entre lobjet et le spot,
	// 2 cas de figure-> si cest ponctuel on calcule la direction, sinon on la connais deja
	if (c->spot->type & POINT)
		c->vec_obj_light = vector_dir(c->spot_pos, c->hitpoint);
	else if (c->spot->type & DIIR)
		c->vec_obj_light = vectormultby_scalar(vector_normalize(
			new_vector(c->spot->pos[3], c->spot->pos[4], c->spot->pos[5])), -1);
	// calcule le dot.product entre la direction lumiere et normal de lobjet
	c->dot_light_norm = vector_dot(c->vec_obj_light, r->norm);
	// renvoie un coef entre 0 et 1, indiquant si on a de la lumiere ou non
	// applique le coef de shadow a la couleur du spot
	shad = ft_shadow(sc->obj, c, sc);
	c->i_l[c->i] *= (shad);
	// verifie si le plan est dans le bon sens
	if (vector_dot(r->norm, vectormultby_scalar(c->vec_obj_light, -1)) > 0 &&
	tmp->type == PLAN)
		return (0);
	diffuse_shadow_specular_end(c, r, &speculaire, &obj_dotn);
	// renvoie la couleur du pixel (ouf)
	return (c->i_l[c->i] == 0 ? 0 : c->i_l[c->i] * (c->rgb[c->i] *
	c->dot_light_norm + 1 * pow(speculaire, 66)));
}

static void		diffuse_end(t_ray *r, t_obj *tmp, t_color *c, t_scene *sc)
{
	// pour ce pixel (stoque dans r) on parcour tout les spot
	// pour chaque composante dune couleur r,g,b ->
	// on ajoute a col chaque coef des spot selon le type diffuse ou speculaire
	// pui on termine par la couleur ambiante
	while (++c->i < 3)
	{
		c->spot = sc->spot;
		c->col = 0;
		while (c->spot)
		{
			c->col = c->col + diffuse_shadow_specular(r, c, sc, tmp);
			c->spot = c->spot->next;
		}
		// ajoute la lum ambiante
		c->intensity[c->i] = sc->amb[1] * c->rgb[c->i] * c->i_a[c->i] + c->col;
	}
}

int				diffuse(t_scene *sc, t_ray *r, double nearest, int col)
{
	t_color	c;
	t_obj	*tmp;

	tmp = r->obj;
	// grace a start et distance on calcule le point dimpact
	c.hitpoint = get_hitpoint(r->start, r->dir, nearest);
	// si c un complexe on calcule la couleur sur l'objet touché
	if (!(tmp->type & COMPLEXE))
		color_composants((!(tmp->text)) ? tmp->c_o
			: texture(tmp, c.hitpoint), c.rgb);
	else
		color_composants(col, c.rgb); // sinon la couleur de l'objet
	color_composants(sc->amb[0], c.i_a); // prepare la couleur de lambiance
	// on substrat hitpoint a start et on normalise ce qui donne la direction de la cam vers lobjet
	c.vec_obj_eye = vector_normalize(vector_sub(r->start, c.hitpoint));
	// on positionne la normal du plan vers la camera
	if (tmp->type == PLAN && vector_dot(c.vec_obj_eye, r->norm) < 0)
		r->norm = vectormultby_scalar(r->norm, -1);
	c.i = -1;
	c.spot = sc->spot;
	// lance la boucle pour ce pixel, additionne le resultat de la conmposante couleur
	// de chaque spot (diffuse + speculaire) et enfin ambiante
	diffuse_end(r, tmp, &c, sc);
	// (?) effet
	if (tmp->eff[4])
		color_normalize(c.intensity, c.intensity,
			noise(r, c.hitpoint, tmp->eff[5]), 0);
	return (colorfromrgb(c.intensity));
}
