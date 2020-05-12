##
## EPITECH PROJECT, 2019
## Day_10
## File description:
## makefile
##
.PHONY : clean fclean re

SRC	=	main.c \
		src/display.c \
		src/cd.c \
		src/cd_2.c \
		src/un_set_env.c \
		src/un_set_env_2.c \
		src/builtin.c \
		src/builtin_2.c \
		src/splitter.c \
		src/my_str_to_word_array.c \
		src/child.c \
		src/child_2.c \
		src/child_3.c \
		src/cmd.c \
		src/cmd_2.c \
		src/forking.c \
		src/forking_2.c

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

$(NAME):	$(OBJ)
		gcc -g -o $(NAME) $(SRC)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean $(NAME)
