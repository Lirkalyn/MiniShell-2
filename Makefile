##
## EPITECH PROJECT, 2019
## Day_10
## File description:
## makefile
##
.PHONY : clean fclean re

SRC	=	main.c \
		display.c \
		builtin.c \
		builtin2.c \
		splitter.c \
		my_str_to_word_array.c \
		child.c \
		child2.c \
		cmd.c \
		cmd_2.c \
		forking.c

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

$(NAME):	$(OBJ)
		gcc -g -o $(NAME) $(SRC)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean $(NAME)
