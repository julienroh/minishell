/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/03/05 17:36:34 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*g_data;

static void	print_redirs(t_redir *redir)
{
	t_redir	*current;
	int		i;

	i = 0;
	current = redir;
	while (current != NULL)
	{
		printf("redir_char %d : %s\n", i, current->target);
		printf("redir_type %d : %d\n", i, current->type);
		i++;
		current = current->next;
	}
}

static void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("arg %d = %s\n", i, argv[i]);
		i++;
	}
}

static void	print_command(t_data *data)
{
	t_command	*current;
	int			i;

	i = 0;
	current = data->cmd_table;
	while (current != NULL)
	{
		printf("command %d :\n", i);
		print_argv(current->argv);
		print_redirs(current->redirs);
		i++;
		printf("\n");
		current = current->next;
	}
}

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

static void	waiting_function(t_data *data)
{
	while (1)
	{
		data->line = readline("minishell$ ");
		if (check_exit(data->line))
			break ;
		if (is_blank_line(data->line))
			continue ;
		data->lexer = lexer_parse_line(data);
		if (check_syntax_tokens(data->lexer, data->lexer->token_total) == 1)
		{
			add_history(data->line);
			free(data->line);
			continue ;
		}
		if (!data->lexer)
		{
			add_history(data->line);
			free(data->line);
			continue ;
		}
		if (lexer_expand(data) == 1)
		{
			add_history(data->line);
			free(data->line);
			continue ;
		}
		data->cmd_table = initialize_command(data, data->lexer);
		print_command(data);
		add_history(data->line);
		free_data_except_env(data);
	}
}

static void	handler(int sig)
{
	printf("Signal recu : %d\n", sig);
	//free_all(g_data);
	waiting_function(g_data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	g_data = &data;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);

	(void)argc;
	(void)argv;
	data.env = parser_env(&data, env);
	data.line = NULL;
	data.lexer = NULL;
	data.cmd_table = NULL;
	data.last_status = 0;
	if (!data.env)
	{
		perror("malloc");
		exit(1);
	}
	waiting_function(&data);
	free_env(data.env);
	return (0);
}
