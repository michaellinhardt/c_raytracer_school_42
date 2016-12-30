NAME = libft.a

SRCS = ft_printf.c ./arg_decimal.c ./arg_string.c ./arg_base_dec.c ./ft_memset.c ./ft_bzero.c ./ft_memcpy.c ./ft_memccpy.c ./ft_memmove.c ./ft_memchr.c ./ft_memcmp.c ./ft_strlen.c ./ft_strdup.c ./ft_strcpy.c ./ft_strncpy.c ./ft_strcat.c ./ft_strncat.c ./ft_strlcat.c ./ft_strchr.c ./ft_strrchr.c ./ft_strstr.c ./ft_strnstr.c ./ft_strcmp.c ./ft_strncmp.c ./ft_atoi.c ./ft_isalpha.c ./ft_isdigit.c ./ft_isalnum.c ./ft_isascii.c ./ft_isprint.c ./ft_toupper.c ./ft_tolower.c ./ft_memalloc.c ./ft_memdel.c ./ft_strnew.c ./ft_strclr.c ./ft_striter.c ./ft_striteri.c ./ft_strmap.c ./ft_strmapi.c ./ft_strequ.c ./ft_strnequ.c ./ft_strsub.c ./ft_strjoin.c ./ft_strtrim.c ./ft_strsplit.c ./ft_itoa.c ./ft_putchar.c ./ft_putstr.c ./ft_putendl.c ./ft_putnbr.c ./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putnbr_fd.c ./ft_putendl_fd.c ./ft_strdel.c ./ft_tab_char.c ./ft_strrev.c ./ft_lstlen.c ./ft_lstmap.c ./ft_lstnew.c ./ft_lstdelone.c ./ft_lstdel.c ./ft_lstadd.c ./ft_lstiter.c ./ft_lst_backadd.c ./ft_puttabl.c ./ft_putnbrl.c ./get_next_line.c ./ft_sizeint.c ./ft_putstr_uni.c ./ft_putfloat.c ./ft_itoa_base.c ./ft_print_mem.c ./ft_wconvchar.c ./ft_wconvstr.c ./initiate_tab.c ./ft_itoau.c ./ft_sizeintu.c ./needed_for_all.c ./needed_for_argstr.c ./needed_for_argstr_two.c ./analyse_format.c ./needed_for_mainfct.c ./needed_for_mainfct_two.c ./arg_bonus.c ./arg_bonus_two.c ./needed_for_bonus.c ./ft_strchr_c.c ./ft_atob.c

OBJS = $(SRCS:.c=.o)

GCCF = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c ./includes/
	gcc $(GCCF) -c -I ./includes $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re