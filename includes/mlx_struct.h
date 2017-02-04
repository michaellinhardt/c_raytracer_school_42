/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytra_gen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:12:41 by ocarta-l          #+#    #+#             */
/*   Updated: 2017/02/04 09:37:01 by mlinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

# define EDIT_BOOL 0x1

# include "mlx_pre.h"
# include "mlx_input.h"
# include "mlx_notif.h"

/*
** pilote quel menu est dessiner a lecran
*/
typedef struct		s_menu
{
	char			draw;
	enum e_menu		id;
	enum e_menu		next;
	char			*new_scene;
	char			*new_object;
	char			*new_spot;
	struct s_scene	*scene;
	struct s_spot	*spot;
	struct s_obj	*obj;
	char			edit_mode;
	int				obj_type;
	int				filter_id;
	int				filter[14];
	int				spot_type;
	int				loading;
}					t_menu;

/*
** pour les liste de type fichier, spot, objet
*/
typedef struct		s_flst
{
	char			*path;
	char			*path_preview;
	struct s_scene	*scene;
	struct s_spot	*spot;
	struct s_obj	*obj;
	int				top[2];
	int				bot[2];
	int				id;
	int				over;
	int				actif;
	t_img			preview;
	struct s_flst	*p;
	struct s_flst	*n;
}					t_flst;

/*
** lien vers toutes les donnée
*/
typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	t_menu			menu;
	t_flst			*flst;
	int				total_file;
	t_input			input;
	char			loop;
	char			loopstop;
	enum e_scene	scene;
	char			img_isload[SCENE_MAX];
	t_img			scene_img[SCENE_MAX][SCENE_IMG_MAX];
	t_get			get[GET_APP_MAX];
	t_get			*getfocus;
	t_img			getcursor;
	struct s_notif	*notif;
	int				winx;
	int				winy;
}					t_mlx;

#endif
