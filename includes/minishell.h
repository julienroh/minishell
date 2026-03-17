/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:34 by adavid            #+#    #+#             */
/*   Updated: 2026/03/17 15:42:12 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <termios.h>

extern volatile sig_atomic_t	g_sig;

typedef struct s_multi
{
	pid_t	*pids;
	int		**pipefd;
	int		n_cmd;
	int		i;
}	t_multi;

typedef struct s_expand
{
	char	*prefix;
	char	*suffix;
	char	*val;
	char	*id;
	char	*tmp;
	char	*new_part;
}	t_expand;

typedef enum e_builtin
{
	CD,
	PWD,
	EXPORT,
	ENV,
	B_ECHO,
	UNSET,
	EXIT,
	CMD,
}	t_btn;

typedef enum e_assign_type
{
	NONE,
	SET,
	APPEND,
}	t_a_ty;

typedef struct s_env
{
	char			*id;
	char			*value;
	int				printable;
	struct s_env	*next;
}	t_env;

typedef struct s_state
{
	int		s_quote;
	int		d_quote;
}				t_state;

typedef struct s_part
{
	char			*value;
	int				expand;
	struct s_part	*next;
}				t_part;

typedef enum e_toktype
{
	WORD,
	PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_toktype;

typedef struct s_token
{
	t_part			*parts;
	t_toktype		type;
	char			*value;
}				t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	int		token_total;
	int		token_i;
}				t_lexer;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_argv
{
	char			*arg;
	struct s_argv	*next;
}	t_argv;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
	int				was_heredoc;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	t_argv				*list_argv;
	t_redir				*redirs;
	struct s_command	*next;
}	t_com;

typedef struct s_data
{
	char			*line;
	char			**args;
	t_lexer			*lexer;
	t_env			*env;
	t_com			*cmd_table;
	int				last_status;
	struct termios	original_term;
}	t_data;

typedef struct s_stdio
{
	int	saved_stdin;
	int	saved_stdout;
}	t_stdio;

typedef struct s_pipe_ctx
{
	int		prev_read;
	int		pipefd[2];
	pid_t	*pids;
	int		n_cmd;
}	t_pipe_ctx;

//errors

void	print_error(char *msg);
void	print_error_identifier(char *str);

//exec

void	executor_run(t_data *data);
bool	is_only_assignment_no_cmd(char **argv, int assign_count);
int		apply_prefix_assignments(t_env **env, char **argv, int assign_count);
t_btn	is_builtin(char *exec_argv);
pid_t	safe_fork(void);
int		exec_external_cmd(t_data *data);
int		restore_stdio(t_stdio *stdio);
int		save_stdio(t_stdio *stdio);
int		apply_redirections(t_redir *redirs);
int		wrapper_apply_redirs(t_data *data, t_stdio *stdio);
int		ft_findpath(char **out_path, char *cmd, char **envp);
int		exec_single_command(t_data *data);
int		exec_builtin_parent(t_data *data, char **exec_cmd);
int		heredoc_cleanup(t_data *data);
int		heredoc_cleanup_str(t_data *data, int fd, char *str);
int		init_v(t_data *data, t_multi *v, int n_cmd);
void	child_setup_pipes(t_multi *v, int i, t_data *data);
int		spawn_child(t_multi *v);
bool	is_last_cmd(int cmdnumber, int i);
int		exec_multi_command(t_data *data, int n_cmd);
void	multi_init_envp(t_data *data, t_multi *v, char ***envp);
int		multi_init_path(t_com *cmd, char **envp, char **path);
int		handle_heredoc(t_data *data, t_redir *r, int counter);
int		heredoc_success_change_redirtype(t_redir *r, t_data *data, char *name);
void	heredoc_sigint_cleanup(int fd, char *name, t_data *data);
void	heredoc_delim_cleanup(int fd, char *line, char *name, t_data *data);
void	cleanup_tmpfiles_heredocs(t_data *data);
int		is_delim(char *line, char *delim);
int		is_directory(const char *path);
int		prepare_all_heredocs(t_data *data);
void	single_execve_error(t_data *data, char **envp, char *path);
void	signal_mute_parent(void);
void	wait_pid_signaled(t_data *data, int wstatus,
			int *sigint_printed, int *sigquit_printed);
void	single_init_envp(t_data *data, char ***envp);
void	single_free_exit(t_data *data, int code);
void	free_structv(t_multi *v);

	//free utilisé dans exec
void	free_cmdtable(t_data *data);
void	free_env_list(t_env *env);
void	free_double_array(char **array);
void	free_envp_path(char **envp, char *path);
void	free_exit_wrapper_child(t_data *data, t_multi *v, int exit_int);

	//assignments

int		get_assignment_name_len(char *word, t_a_ty type);
int		count_prefix_assignments(char **argv);
int		check_malloc_ok(char *str);
int		apply_one_assignment(t_env **env, char *word);
void	lst_add_back(t_env **env, t_env *new);
int		assign_already_in_list(t_env *env, char *id, char *value, t_a_ty type);
int		handle_assignment_only_command(t_data *data, int assign_count);
t_a_ty	get_assignment_type(char *word);
t_env	*env_dup_list(t_env *src);
t_env	*lst_env_new(char *name, char *value);
char	**env_to_envp(t_env *env);
int		count_cmd_numbers(t_data *data);

//builtin

int		exec_cd(t_data *data, char **args);
int		exec_echo(t_data *data, char **args);
int		exec_env(t_env *env);
int		exec_export(t_data *data, char **args, int i);
int		exec_pot_export(t_data *data, char **args);
int		exec_pwd(t_env *env);
int		exec_unset(char **args, t_env **env, int i);
int		only_export(t_data *data, int i);
int		exec_exit(t_data *data, char **args);

//check

int		check_syntax_tokens(t_lexer *lexer, int number);

//command

t_com	*initialize_command(t_data *data, t_lexer *lexer);

//free

void	free_env(t_env *env);
void	free_data_except_env(t_data *data);
void	free_all_malloc(t_data *data);
void	free_list_argv(t_com *cmd);
void	free_all(t_data *data);

//lexer

t_lexer	*lexer_parse_line(t_data *data);
int		lexer_expand(t_data *data);

//parser_env

t_env	*parser_env(t_data *data, char **env);

//prompt

void	waiting_function(t_data *data);

//signal

void	signal_exec(void);
void	signal_heredoc(void);
void	signal_prompt(void);

//UTILS

//comand_utils.c

void	add_redir(t_redir **redir, t_data *data, int i, char *target);
void	from_list_to_array(t_data *data, t_com *head);

//export_utils.c

int		already_in_struct(t_env *env, char *id, char *value, int plus);
int		check_identifier(char *id);
void	plus_equal_condition(t_data *data, char *id, int printable);

//export_utils_2.c

char	*get_identifier(t_data *data, char *arg);
char	*get_value(t_data *data, char *arg);
int		max(char *arg_a, char *arg_b);
void	swap(char **arg_a, char **arg_b);
void	free_char_env(char **char_env);

//lexer_utils.c

void	change_state_dquote(t_state *state);
void	change_state_squote(t_state *state);
t_part	*last_part(t_token *token);
void	add_new_part(t_data *data, t_token *token, int expand);
void	add_char(t_data *data, t_token *token, char c);

//lexer_utils_2.c

int		is_operator(char c);
int		test_if_new_part(t_data *data, t_token *tok, int expand, int new_part);
int		count_operator_case(char *line, int *i, int count);
void	set_operator_token(t_data *data, char *line, t_lexer *lexer, int *i);

//lexer_utils_3.c

void	expand_part(t_data *data, t_part *p, int i);

//parser_utils.c

int		free_new(t_env *new, char *str);
t_env	*env_new(t_data *data, char *str);
void	env_add_back(t_env **env, t_env *new);

//utils.c

int		is_redir(t_token *tok);
int		is_space(char c);
int		size_env(t_env *env);
void	invalid_export(char *id, char *value, char *arg);
int		define_size(t_env *env);

#endif
