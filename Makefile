NAME = RT

SRCSPATH = srcs/
INCLUDES = includes/
LIBFT_INCLUDES = libft/includes

SRCS = main.c\
	  error.c\
	  parse.c\
	  parse_cam.c\
	  parse_fct.c\
	  parse_col_amb.c\
	  parse_size_eff.c\
	  parse_objects.c\
	  raytracing.c\
	  ray_touch.c\
	  write_img.c\
	  mouse_functions.c\
	  key_functions.c\
	  vector_functions.c\
	  threads.c\
	  shadow_max.c\
	  write_scene.c\
	  matrice_rot.c\
	  intersectray_plane.c\
	  intersectray_cylindre1.c\
	  intersectray_cylindre2.c\
	  intersectray_triangle.c\
	  intersectray_complex.c\
	  intersectray_sphere.c\
	  intersectray_carre.c\
	  intersectray_ellipse.c\
	  intersectray_boloid.c\
	  intersectray_cone.c\
	  equa_sec.c\
	  cut_object.c\
	  color_functions.c\
	  perlin.c\
	  texture.c\
	  parse_triangle.c\
	  interface/builder.c\
	  interface/draw.c\
	  interface/hook.c\
	  interface/scene_handler.c\
	  interface/object_handler.c\
	  interface/object_model.c\
	  interface/spot_handler.c\
	  interface/spot_model.c\
	  interface/text_interface.c\
	  interface/filter_handler.c\
	  filter_part1.c\
	  filter_part2.c\
	  filter_part3.c


SRC = $(addprefix $(SRCSPATH), $(SRCS))

GTK_FLAGS = `pkg-config --cflags gtk+-3.0`

GTK_LIBS = `pkg-config --libs gtk+-3.0`

WFLAGS = -Wall -Werror -Wextra -g -march=native $(GTK_FLAGS)

LFLAGS = -L libft/ -lft -lm -lmlx -framework OpenGL -framework AppKit $(GTK_LIBS)

CC = gcc -g

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(LIBFT_INCLUDES) -I $(INCLUDES) $< -o $@

$(NAME) : $(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS) -I $(INCLUDES) 

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

sdl_install :
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/

re : fclean all

lre :
	make -C libft/ re

.PHONY: all clean fclean re
