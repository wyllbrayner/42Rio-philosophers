SRCS		= src/ft_00-main.c src/ft_01-check_input.c src/ft_02-start.c src/ft_03-00_actions.c \
				src/ft_03-01_meals.c src/ft_04-monitor.c src/ft_05-time.c src/ft_06-utils.c
OBJS		= $(SRCS:.c=.o)
NAME		= philo
RM			= rm -f
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norminette:
	norminette -R CheckDefineForbiddenSourceHeader

.PRONH: all $(NAME)
