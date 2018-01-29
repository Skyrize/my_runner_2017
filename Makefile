##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## all clean fclean re
##

SRC	=	main.c	\
		destroy_functions.c	\
		menu_gesture_functions.c	\
		input_gesture_functions.c	\
		map_loader.c	\
		obstacles_gesture_functions.c	\
		player_gestures_functions_and_also_text.c	\
		create_one.c	\
		create_two.c	\
		objs_list_creation.c	\
		restart_game.c	\
		move_rects.c	\
		init_functions.c	\
		set_and_reset_game_opts.c	\
		game_computing_functions.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_runner

GFLAGS	=	-lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -L./lib/my -lmy

CC	=	gcc -Wall -Wextra -Werror -W

all:	prepare_lib $(NAME)

prepare_lib:
	make -C lib/my

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(GFLAGS) -lm

clean:
	make clean -C lib/my
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
