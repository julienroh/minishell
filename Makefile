NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes -I libft -I libft/get_next_line
LDFLAGS = -lreadline

RM = rm -rf

SRC =	src/main/main.c \
		src/analyze/analyze_args.c \
		src/errors/errors.c \
		src/builtin/builtin_echo.c \
		src/builtin/builtin_export.c \
		src/builtin/builtin_unset.c \
		src/builtin/builtin_env.c \
		src/builtin/builtin_cd.c \
		src/builtin/builtin_pwd.c \
		src/builtin/builtin_pot_export.c \
		src/builtin/only_export.c \
		src/lexer/lexer_expand_to_args.c \
		src/lexer/lexer_parse_line.c \
		src/parser_env/parser_env.c \
		src/command/initialize_command.c \
		src/utils/export_utils.c \
		src/utils/export_utils_2.c \
		src/utils/lexer_utils.c \
		src/utils/parser_utils.c \
		src/utils/utils.c \

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
