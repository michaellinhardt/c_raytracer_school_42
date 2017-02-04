NAME = RT

SRCSPATH = srcs/
INCLUDES = includes/
LIBFT_INCLUDES = libft/includes

SRCS = 	main.c \
		raytracing.c \
		error.c \
		parse.c \
		parse_next.c \
		parse_cam.c \
		parse_fct.c \
		parse_col_amb.c \
		parse_size_eff.c \
		parse_objects.c \
		parse_objects_next.c \
		ray_touch.c \
		write_img.c \
		vector_functions.c \
		vector_functions_next.c \
		vector_functions_bis.c \
		threads.c \
		diffuse.c \
		refraction.c \
		reflexion.c \
		getnearest.c \
		write_scene.c \
		write_scene_spot.c \
		write_scene_col.c \
		write_scene_type.c \
		matrice_rot.c \
		intersectray_plane.c \
		intersectray_cylindre1.c \
		intersectray_cylindre2.c \
		intersectray_triangle.c \
		intersectray_complex.c \
		intersectray_sphere.c \
		intersectray_carre.c \
		intersectray_ellipse.c \
		intersectray_boloid.c \
		intersectray_cone.c \
		intersectray_cone2.c \
		equa_sec.c \
		ft_shadow.c \
		cut_object.c \
		color_functions.c \
		perlin.c \
		perlin_next.c \
		texture.c \
		add_vector_triangle.c \
		parse_lst_triangle.c \
		parse_triangle.c \
		filter_part1.c \
		filter_part2.c \
		filter_part3.c \
		filter_part4.c \
		mlx_keytochar.c \
		mlx_notif.c \
		mlx_menu_btn.c \
		mlx_menu_free_list.c \
		mlx_menu_draw.c \
		mlx_menu_btn_left.c \
		mlx_menu_btn_right.c \
		mlx_menu_edit_del_btn_open.c \
		mlx_menu_edit_mod_btn_open.c \
		mlx_menu_edit_switch_btn_open.c \
		mlx_menu_edit_add_btn_open.c \
		mlx_menu_object_btn_open.c \
		mlx_menu_object_clic.c \
		mlx_menu_object_mod_btn_type.c \
		mlx_menu_object_add_btn.c \
		mlx_menu_object_del_btn.c \
		mlx_menu_scene_del_btn.c \
		mlx_menu_scene_add_btn.c \
		mlx_menu_scene_btn_open.c \
		mlx_menu_scene_clic.c \
		mlx_menu_load_btn_open.c \
		mlx_menu_load_btn_nav.c \
		mlx_menu_load_clic.c \
		mlx_menu_spot_btn_open.c \
		mlx_menu_spot_clic.c \
		mlx_menu_spot_mod_btn_type.c \
		mlx_menu_spot_add_btn.c \
		mlx_menu_spot_del_btn.c \
		mlx_menu_save_btn_open.c \
		mlx_menu_camera_btn_open.c \
		mlx_menu_gen_btn.c \
		mlx_menu_filter_btn.c \
		mlx_redraw.c \
		mlx_hook.c \
		mlx_hook_keyboard.c \
		mlx_loop.c \
		mlx_img.c \
		mlx_layer.c \
		mlx_mouse_release.c \
		mlx_mouse_release_img.c \
		mlx_mouse_release_flst.c \
		mlx_mouse_release_get.c \
		mlx_mouse_over.c \
		mlx_scene.c \
		mlx_scene_img_load.c \
		mlx_scene_init.c \
		mlx_scene_init_0_intro.c \
		mlx_scene_init_1_rt.c \
		mlx_scene_build.c \
		mlx_scene_0_intro.c \
		mlx_scene_1_rt.c \
		mlx_scene_text.c \
		mlx_scene_text_menu.c \
		mlx_scene_text_menu_next.c \
		mlx_scene_text_menu_bis.c \
		mlx_scene_text_input.c \
		mlx_scene_input.c \
		mlx_input_action.c \
		mlx_input_valid.c \
		mlx_input_valid_next.c \
		mlx_input_char.c \
		mlx_input_char_next.c \
		mlx_input_draw_box.c \
		mlx_input_draw_cursor.c \
		mlx_input_target_str.c \
		mlx_check_area.c \
		mlx_scene_init_1_rt_img_0.c \
		mlx_scene_init_1_rt_img_1.c \
		mlx_scene_init_1_rt_img_2.c \
		mlx_scene_init_1_rt_img_3.c \
		mlx_scene_init_1_rt_img_4.c \
		mlx_scene_init_1_rt_img_5.c \
		mlx_scene_init_1_rt_img_6.c \
		mlx_scene_init_1_rt_get_1.c \
		mlx_scene_init_1_rt_get_2.c \
		mlx_scene_init_1_rt_get_3.c \
		mlx_start.c


SRC = $(addprefix $(SRCSPATH), $(SRCS))

WFLAGS = -Wall -Werror -Wextra -march=native -O3

LFLAGS = -L libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit
MIKAFLAGS = -L libft/ -lft -L minilibx/ -lmlx -framework OpenGL -framework AppKit

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(LIBFT_INCLUDES) -I $(INCLUDES) $< -o $@

$(NAME) : $(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS) -I $(INCLUDES)

lib:
	make -C libft re

clean :
	rm -rf $(OBJ)
	make -C libft clean

img :
	@mkdir image

clean_si :
	@rm -rf image
	@rm -rf scene

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all

rt : cleanrt all
	@./$(NAME)

cleanrt :
	rm -f $(NAME)
	rm -rf $(OBJ)

lre :
	make -C libft/ re

.PHONY: all clean fclean re
