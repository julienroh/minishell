/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 08:37:06 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 10:52:36 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_env(t_env *env)
// {
// 	t_env	*current;

// 	current = env;
// 	while (current != NULL)
// 	{
// 		printf("id = %s / value = %s / printable = %d\n", current->id, current->value, current->printable);
// 		current = current->next;
// 	}
// }

// static void	print_redirs(t_redir *redir)
// {
// 	t_redir	*current;
// 	int		i;

// 	i = 0;
// 	current = redir;
// 	while (current != NULL)
// 	{
// 		printf("redir_char %d : %s\n", i, current->target);
// 		printf("redir_type %d : %d\n", i, current->type);
// 		i++;
// 		current = current->next;
// 	}
// }

// static void	print_argv(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("arg %d = %s\n", i, argv[i]);
// 		i++;
// 	}
// }

// static void	print_command(t_data *data)
// {
// 	t_command	*current;
// 	int			i;

// 	i = 0;
// 	current = data->cmd_table;
// 	while (current != NULL)
// 	{
// 		printf("command %d :\n", i);
// 		print_argv(current->argv);
// 		print_redirs(current->redirs);
// 		i++;
// 		printf("\n");
// 		current = current->next;
// 	}
// }

static int	check_exit(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

static int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	free(line);
	return (1);
}

/*Fonction that wait for an entry in the terminal
and parse the line to split it in args that will be analyse
to execute commands*/

void	waiting_function(t_data *data)
{
	int	stdin_backup;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	stdin_backup = dup(STDIN_FILENO);
	while (1)
	{
		g_sig = 0;
		signal_prompt();
		data->line = readline("minishell$ ");
		add_history(data->line);
		if (g_sig == SIGINT)
		{
			data->last_status = 130;
			free(data->line);
			data->line = NULL;
			dup2(stdin_backup, STDIN_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			continue ;
		}
		if (check_exit(data->line))
			 break ;
		if (is_blank_line(data->line))
			continue ;
		data->lexer = lexer_parse_line(data);
		if (!data->lexer)
		{
			add_history(data->line);
			free_data_except_env(data);
			continue ;
		}
		if (check_syntax_tokens(data->lexer, data->lexer->token_total) == 1)
		{
			add_history(data->line);
			free_data_except_env(data);
			continue ;
		}
		if (lexer_expand(data) == 1)
		{
			add_history(data->line);
			free_data_except_env(data);
			continue ;
		}
		data->cmd_table = initialize_command(data, data->lexer);
		executor_run(data);
		//print_env(data->env);
		//print_command(data);
		free_data_except_env(data);
	}
}
