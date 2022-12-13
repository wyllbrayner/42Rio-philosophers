SRCS		= $(wildcard src/*.c)
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
