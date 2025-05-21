# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 18:20:53 by gribeiro          #+#    #+#              #
#    Updated: 2025/05/21 01:32:28 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Srcs
SRCS = main.c init.c crt_philos.c freemem.c utils.c routine.c threads.c

SRC = $(addprefix src/, $(SRCS))

OBJS = $(SRC:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

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
	@valgrind --leak-check=full --show-leak-kinds=all -s ./philo 10 200 200 200

.PHONY: all clean fclean re
