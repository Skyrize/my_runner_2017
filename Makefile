##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## all clean fclean re
##

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_runner

GFLAGS	=	-lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -L./lib/my -lmy

CC	=	gcc -Wall -Wextra -Werror -W

CFLAGS	=	-g3

all:	prepare_lib $(NAME)

prepare_lib:
	make -C lib/my

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(GFLAGS) $(CFLAGS) -lm

clean:
	make clean -C lib/my
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
