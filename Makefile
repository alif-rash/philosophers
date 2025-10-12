NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -pthread

# Colors
BLUE = \033[0;94m
GREEN = \033[0;92m
YELLOW = \033[0;93m
RED = \033[0;91m
RESET = \033[0m

SRCS = 	main.c        \
		parsing.c     \
		utils.c       \
		init.c        \
		actions.c     \
		routine.c     \
		simulation.c  \
		time_utils.c

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✅ Philosophers compiled successfully!$(RESET)"
	@echo "$(YELLOW)💡 Usage: ./$(NAME) <philos> <die> <eat> <sleep> [meals]$(RESET)"

$(OBJ_DIR)/%.o: %.c philo.h | $(OBJ_DIR)
	@printf "$(BLUE)Compiling: $(RESET)%-30s" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)🗑️  Object files cleaned$(RESET)"; \
	else \
		echo "$(YELLOW)⚠️  Nothing to clean$(RESET)"; \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		$(RM) $(NAME); \
		echo "$(RED)🗑️  Executable removed$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re