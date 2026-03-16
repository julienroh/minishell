/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 08:37:06 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 11:40:59 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ctrl_c_case(t_data *data, int stdin_backup)
{
	data->last_status = 130;
	free(data->line);
	data->line = NULL;
	dup2(stdin_backup, STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	wraper_end_of_function(t_data *data)
{
	data->cmd_table = initialize_command(data, data->lexer);
	executor_run(data);
	free_data_except_env(data);
}

/*Fonction that wait for an entry in the terminal
and parse the line to split it in args that will be analyse
to execute commands*/

void	waiting_function(t_data *data, int stdin_backup)
{
	while (1)
	{
		g_sig = 0;
		signal_prompt();
		data->line = readline("minishell$ ");
		if (data->line)
			add_history(data->line);
		if (g_sig == SIGINT)
		{
			ctrl_c_case(data, stdin_backup);
			continue ;
		}
		if (check_exit(data->line))
			break ;
		if (is_blank_line(data->line))
			continue ;
		data->lexer = lexer_parse_line(data);
		if (!data->lexer || lexer_expand(data) == 1
			|| check_syntax_tokens(data->lexer, data->lexer->token_total) == 1)
		{
			free_data_except_env(data);
			continue ;
		}
		wraper_end_of_function(data);
	}
}
