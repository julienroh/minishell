/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:34 by adavid            #+#    #+#             */
/*   Updated: 2026/03/10 10:12:58 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "stdbool.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef	struct s_expand
{
	char	*prefix;
	char	*suffix;
	char	*val;
	char	*id;
	char	*tmp;
	char	*new_part;
}	t_expand;


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

typedef enum e_toktype //le type du token
{
	WORD, //grep, ls, -l, "lorem $VAR", 'lorem'
	PIPE, // |
	T_IN, // <
	T_OUT, // >
	T_APPEND, // >>
	T_HEREDOC, // <<
}	t_toktype;

typedef struct s_token
{
	t_part	*parts;
	t_toktype		type; //word, pipe...
	char			*value; //grep, <, <<, ls, -n, etc..
}				t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	int		token_total;
	int		token_i;
}				t_lexer;

// pour la cmd table :

typedef enum e_redir_type
{
	R_IN, // <
	R_OUT, // >
	R_APPEND, // >>
	R_HEREDOC // <<
}	t_redir_type;

typedef struct s_argv
{
	char 	*arg;
	struct s_argv	*next;
}	t_argv;

typedef struct s_redir //liste chainee de redirs. 1ere redir rencontree va a la fin (add la node a la fin de la liste). --> conserve l'ordre dentree des inputs.
{
	t_redir_type	type; //cf t_redir_type
	char			*target; //in.txt, out.txt, etc... check l'arg apres le type de redir. (ex : < in.txt)
	struct s_redir	*next; //prochaine redirection rencontree, pour la CMD. 1 CMD peut avoir plusieurs redir. (ex : cat < in.txt > out.txt)
}	t_redir;

typedef struct s_command //une node de la liste chainee de la cmd table.
{
	char				**argv;
	t_argv				*list_argv; //juste changer le s pour un v ici (plus facile a capter pour execve)
	t_redir				*redirs; //liste chainee des redirs pour 1 cmd.
	struct s_command	*next; //next cmd.
}	t_command;

typedef struct	s_data
{
	char		*line;
	char		**args;
	t_lexer		*lexer;
	t_env		*env;
	t_command	*cmd_table;
	int			last_status;
}	t_data;

typedef struct s_exec_data
{
	char	**envp;
	char	**exec_argv;
	int		assign_count;
}	t_exec_data;
//var pour mes execs. NEED

//type des assigns. NEED
typedef enum e_assign_type
{
	NONE,
	SET,
	APPEND,
}	t_assign_type;

typedef enum e_builtin
{
	CD,
	PWD,
	EXPORT,
	ENV,
	ECHO,
	UNSET,
	EXIT,
	CMD,
}	t_builtin;

//errors 

void	print_error(char *msg);
void	print_error_identifier(char *str);

//exec
void		executor_run(t_data *data);
bool		is_only_assignment_no_cmd(char **argv, int assign_count);
int			apply_prefix_assignments(t_env **env, char **argv, int assign_count);
t_builtin	is_builtin(char *exec_argv);
int			exec_builtin_parent(char **exec_cmd, char **envp);
pid_t		safe_fork(void);

	//free utilisé dans exec
void	free_cmdtable(t_data *data);
void	free_env_list(t_env *env);
void	free_double_array(char **array);
void 	wrapper_free_single_command(t_exec_data *ctx);
int		exec_external_cmd(t_data *data, t_exec_data *ctx);

	//assignments
int				get_assignment_name_len(char *word, t_assign_type type);
int				count_prefix_assignments(char **argv);
int				check_malloc_ok(char *str);
int				apply_one_assignment(t_env **env, char *word);
t_env			*lst_env_new(char *name, char *value);
void			lst_add_back(t_env **env, t_env *new);
int				assign_already_in_list(t_env *env, char *id, char *value,
				t_assign_type type);
t_assign_type 	get_assignment_type(char *word);
int				handle_assignment_only_command(t_data *data, t_exec_data *ctx);
t_env 			*env_dup_list(t_env *src); //noneed ?
char			**env_to_envp(t_env *env); 
int				init_exec_data(t_exec_data	*exec_ctx, t_data *data);
int				count_cmd_numbers(t_data *data);

		//debug exec, a virer
void print_list_env(t_env *list);

//builtin

int		exec_cd(t_data *data, char **args);
void	exec_echo(t_data *data, char **args);
void	exec_env(t_env *env);
void	exec_export(t_data *data, char **args);
int		exec_pot_export(t_data *data, char **args);
int		exec_pwd(t_env *env);
void	exec_unset(char **args, t_env **env);
void	only_export(t_data *data);

//check

int		check_syntax_tokens(t_lexer *lexer, int number);

//command

t_command	*initialize_command(t_data *data, t_lexer *lexer);

//free

void	free_env(t_env *env);
void	free_data_except_env(t_data *data);
void	free_all(t_data *data);
void	free_list_argv(t_command *cmd);

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
void	from_list_to_array(t_data *data, t_command *head);

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

#endif
