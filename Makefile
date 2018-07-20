# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgrigore <rgrigore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/27 21:49:16 by rgrigore          #+#    #+#              #
#    Updated: 2017/12/27 22:00:40 by rgrigore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = ./src/main.c \
		./src/reader.c \
		./src/solver.c

OBJ = main.o reader.o solver.o

FLAGS = -Wall -Werror -Wextra

$(NAME):
	@gcc -c $(FLAGS) $(SRC)
	@gcc -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
