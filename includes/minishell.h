/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:34 by adavid            #+#    #+#             */
/*   Updated: 2026/03/03 11:38:51 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

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

typedef struct s_redir //liste chainee de redirs. 1ere redir rencontree va a la fin (add la node a la fin de la liste). --> conserve l'ordre dentree des inputs.
{
	t_redir_type	type; //cf t_redir_type
	char			*target; //in.txt, out.txt, etc... check l'arg apres le type de redir. (ex : < in.txt)
	struct s_redir	*next; //prochaine redirection rencontree, pour la CMD. 1 CMD peut avoir plusieurs redir. (ex : cat < in.txt > out.txt)
}	t_redir;

typedef struct s_command //une node de la liste chainee de la cmd table.
{
	char				**argv; //juste changer le s pour un v ici (plus facile a capter pour execve)
	t_redir				*redirs; //liste chainee des redirs pour 1 cmd.
	struct s_command	*next; //next cmd.
}	t_command;

typedef struct	s_data
{
	char		*line;
	t_lexer		*lexer;
	t_env		*env;
	t_command	*cmd_table;
	int			last_status;
}	t_data;

//analyse

int		analyze_args(t_data *data);

//errors

void	print_error(char *msg);
void	print_error_identifier(char *str);

//builtin

int		exec_cd(t_data *data);
void	exec_echo(t_data *data);
void	exec_env(t_env *env);
void	exec_export(t_data *data);
int		exec_pot_export(t_data *data);
int		exec_pwd(t_env *env);
void	exec_unset(char **args, t_env **env);
void	only_export(t_data *data);

//free

void	free_env(t_env *env);
void	free_data_except_env(t_data *data);
void	free_all(t_data *data);

//lexer

t_lexer	*lexer_parse_line(t_data *data);
int		lexer_expand(t_data *data);

//parser_env

t_env	*parser_env(t_data *data, char **env);

//UTILS

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

//parser_utils.c

int		free_new(t_env *new, char *str);
t_env	*env_new(t_data *data, char *str);
void	env_add_back(t_env **env, t_env *new);

//utils.c

int		is_space(char c);
int		size_env(t_env *env);
void	invalid_export(char *id, char *value, char *arg);

#endif
