NAME		= philo

SRCDIR		= ./src/
SRCS		= ft_00-main.c ft_01-check_input.c ft_02-start.c ft_03-00_actions.c \
				ft_03-01_meals.c ft_04-monitor.c ft_05-time.c ft_06-utils.c
SRCS		:= $(addprefix $(SRCDIR), $(notdir $(SRCS)))
OBJDIR		= ./obj/
OBJS		= $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))

RM			= rm -rf
COMP		= cc
FLAG		= -Wall -Wextra -Werror -pthread

YELLOW		= \033[33m
GREEN		= \033[32m
RESET		= \033[0m

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(COMP) $(FLAG) -c $< -o $@
	@echo -n "#"

$(NAME): $(OBJS)
	@$(COMP) $(FLAG) $(OBJS) -o $(NAME)
	@echo "\n$(GREEN) 💯 | $(NAME) created.$(RESET)"

clean:
	@$(RM) $(OBJDIR)
	@echo "$(YELLOW) 🧹 | $(OBJDIR) cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW) 🌪️ | $(NAME) cleaned.$(RESET)"

re: fclean all

norm:
	norminette -R CheckDefineForbiddenSourceHeader

.PRONH: all $(NAME) clean fclean re norm
