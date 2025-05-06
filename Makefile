# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 18:20:53 by gribeiro          #+#    #+#              #
#    Updated: 2025/04/04 18:20:53 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

# Srcs
SRCS = main.c

SRC = $(addprefix src/, $(SRCS))

OBJS = $(SRC:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: all
	@valgrind --show-below-main=no --leak-check=full --show-leak-kinds=all \
	--track-fds=yes --track-origins=yes -s -q ./philosophers

.PHONY: all clean fclean re
