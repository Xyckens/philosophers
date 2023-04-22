# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvieira <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 14:42:53 by fvieira           #+#    #+#              #
#    Updated: 2023/04/22 22:16:33 by fvieira          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = main.c \
		auxil.c \
		actions.c \
		lists.c \
		death.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lpthread $(OBJ) -o $(NAME)
	echo "./philo created"

clean: 
	rm -f $(OBJ)
	echo "obj deleted"


fclean: clean 
	rm -f $(NAME)
	echo "./philo deleted"

re: fclean all

.SILENT:

.PHONY: all, re, clean, fclean
