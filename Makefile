# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 18:20:53 by gribeiro          #+#    #+#              #
#    Updated: 2025/05/24 02:38:59 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Srcs
SRCS = main.c init.c crt_philos.c utils.c routine.c threads.c \
	mutex_handler.c freemem.c routine_eat.c

SRC = $(addprefix src/, $(SRCS))

OBJS = $(SRC:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread -pthread

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
	@valgrind --tool=helgrind ./philo 200 800 200 200 10

.PHONY: all clean fclean re
