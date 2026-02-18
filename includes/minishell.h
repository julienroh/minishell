/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:34 by adavid            #+#    #+#             */
/*   Updated: 2026/02/18 17:30:58 by jroh             ###   ########.fr       */
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

typedef struct s_token
{
	t_part	*parts;
}				t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	int		token_total;
	int		token_i;
}				t_lexer;

// typedef struct s_command
// {
// 	int			fd_in;
// 	int			fd_out;
// 	char		**args;
// 	t_command	*next;
// }				t_command;

//analyse

int		analyze_args(char **args, t_env *env);

//errors

void	print_error(char *msg);
void	print_error_identifier(char *str);

//exec

void	exec_echo(char **args);
void	exec_export(char **args, t_env*env);
void	exec_unset(char **args, t_env **env);
void	exec_env(t_env *env);
int		exec_cd(char **args, t_env *env);
int		exec_pwd(t_env *env);
int		exec_pot_export(char **args, t_env *env);
void	only_export(t_env *env);

//lexer

t_lexer	*lexer_parse_line(char *line);
char	**lexer_expand_to_args(t_lexer *lexer, t_env *env);

//parser_env

t_env	*parser_env(char **env);

//UTILS

//export_utils.c

int		already_in_struct(t_env *env, char *id, char *value, int plus);
int		check_identifier(char *id);
void	plus_equal_condition(t_env *env, char *id, int printable);

//export_utils_2.c

char	*get_identifier(char *arg);
char	*get_value(char *arg);

//lexer_utils.c

void	change_state_dquote(t_state *state);
void	change_state_squote(t_state *state);
t_part	*last_part(t_token *token);
void	add_new_part(t_lexer *lexer, char *line, int i);
int		state_change(t_state *state, char c);

//parser_utils.c

int		free_new(t_env *new, char *str);
t_env	*new_without_equal(t_env *new, char *str);
t_env	*new_with_equal(t_env *new, char *str, int i);
t_env	*env_new(char *str);
void	env_add_back(t_env **env, t_env *new);

//utils.c

int		is_space(char c);
int		size_env(t_env *env);
int		invalid_export(char *id, char *value, char *arg);
void	print_exit(char *line);

#endif
