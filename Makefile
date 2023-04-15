# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvieira <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 14:42:53 by fvieira           #+#    #+#              #
#    Updated: 2023/04/15 17:45:54 by fvieira          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

SRC = main.c \
		auxil.c \
		think_sleep.c \
		lists.c

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
