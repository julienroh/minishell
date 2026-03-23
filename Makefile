NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes -I libft -I libft/get_next_line -g
LDFLAGS = -lreadline

RM = rm -rf

SRC =	src/main/main.c \
		src/main/init_no_env_path.c \
		src/main/init_no_env_pwd.c \
		src/main/init_no_env_shlvl.c \
		src/main/init_no_env_underscore.c \
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
		src/utils/export_utils_3.c \
		src/utils/lexer_utils.c \
		src/utils/lexer_utils_2.c \
		src/utils/lexer_utils_3.c \
		src/utils/parser_utils.c \
		src/utils/utils.c \
		src/exec/executor.c \
		src/exec/exec_utils/exec_free_utils.c \
		src/exec/exec_utils/exec_utils.c \
		src/exec/exec_redir/exec_single_redirs.c \
		src/exec/exec_redir/exec_heredoc.c \
		src/exec/exec_redir/exec_heredoc_utils.c \
		src/exec/exec_single_cmd/exec_single.c \
		src/exec/exec_single_cmd/exec_single_utils.c \
		src/exec/exec_single_cmd/exec_stdio_handling.c \
		src/exec/exec_multi_cmd/exec_multi_utils1.c \
		src/exec/exec_multi_cmd/exec_multi_utils2.c \
		src/exec/exec_multi_cmd/exec_multi_utils3.c \
		src/exec/exec_multi_cmd/exec_multi.c \
		src/exec/exec_path/exec_path.c \
		src/exec/exec_path/exec_path_utils.c \
		src/exec/exec_assign/exec_assign_utils.c \
		src/exec/exec_assign/exec_assign_utils2.c \
		src/exec/exec_assign/exec_assign_utils3.c \
		src/exec/exec_assign/exec_assign_utils4.c \
		src/exec/exec_assign/exec_env_to_envp.c \
		src/exec/exec_builtin/exec_builtin.c \
 		src/builtin/builtin_echo.c \
 		src/builtin/builtin_export.c \
 		src/builtin/builtin_unset.c \
 		src/builtin/builtin_env.c \
 		src/builtin/builtin_cd.c \
 		src/builtin/builtin_pwd.c \
		src/builtin/builtin_exit.c \
 		src/builtin/only_export.c \

OBJS = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valtest:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline_leaks.supp ./minishell

valenv:
	env -i valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline_leaks.supp ./minishell

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re valtest

.SILENT:
