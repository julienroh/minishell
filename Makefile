NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes -I libft -I libft/get_next_line
LDFLAGS = -lreadline

RM = rm -rf

SRC =	src/main/main.c \
		src/errors/errors.c \
		src/free/free_all.c \
		src/free/free_data_except_env.c \
		src/free/free_env.c \
		src/free/free_list_argv.c \
		src/lexer/lexer_expand.c \
		src/lexer/lexer_parse_line.c \
		src/check/check_syntax_tokens.c \
		src/parser_env/parser_env.c \
		src/prompt/waiting_function.c \
		src/signal/signal_exec.c \
		src/signal/signal_heredoc.c \
		src/signal/signal_prompt.c \
		src/command/initialize_command.c \
		src/utils/command_utils.c \
		src/utils/export_utils.c \
		src/utils/export_utils_2.c \
		src/utils/lexer_utils.c \
		src/utils/lexer_utils_2.c \
		src/utils/lexer_utils_3.c \
		src/utils/parser_utils.c \
		src/utils/utils.c \
# 		src/builtin/builtin_echo.c \
# 		src/builtin/builtin_export.c \
# 		src/builtin/builtin_unset.c \
# 		src/builtin/builtin_env.c \
# 		src/builtin/builtin_cd.c \
# 		src/builtin/builtin_pwd.c \
# 		src/builtin/builtin_pot_export.c \
# 		src/builtin/only_export.c \ #

OBJS = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(PRINTF) $(MLX) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

.SILENT:
