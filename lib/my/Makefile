##
## EPITECH PROJECT, 2017
## Makefile t01 d10
## File description:
## compil libmy. from files in lib/my/, copy it in lib, copi .h in include
##

SRC	=	my_compute_power_rec.c	\
		my_compute_square_root.c	\
		my_find_prime_sup.c	\
		my_getnbr.c	\
		my_isneg.c	\
		my_is_prime.c	\
		my_putchar.c	\
		my_put_nbr.c	\
		my_putstr.c	\
		my_revstr.c	\
		my_showmem.c	\
		my_showstr.c	\
		my_sort_int_array.c	\
		my_strcapitalize.c	\
		my_strcat.c	\
		my_strcmp.c	\
		my_strcpy.c	\
		my_str_isalpha.c	\
		my_str_islower.c	\
		my_str_isnum.c	\
		my_str_isprintable.c	\
		my_str_isupper.c	\
		my_strlen.c	\
		my_strlowcase.c	\
		my_strncat.c	\
		my_strncmp.c	\
		my_strncpy.c	\
		my_strstr.c	\
		my_strupcase.c	\
		my_swap.c	\
		my_put_ull.c	\
		my_printf.c	\
		my_print_fct1.c	\
		my_print_fct2.c	\
		my_print_fct3.c	\
		my_put_llnbr.c	\
		my_putnbr_base.c	\
		my_double_strcat.c	\
		put_a_square_csfml.c	\
		my_int_to_array.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my

NAMELIB	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc lib$(NAME).a $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
