# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkael <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 12:11:53 by bkael             #+#    #+#              #
#    Updated: 2021/10/05 19:00:30 by bkael            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = init.c \
	main.c \
	print.c \
	pthreads.c

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -I ./ $^ -o $(NAME)

%.o: %.c philo.h
	gcc $(FLAGS) -I ./ -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re