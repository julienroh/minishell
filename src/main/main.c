/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/03/03 14:40:04 by jroh             ###   ########.fr       */
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
		//check_syntax_tokens(data->lexer, data->lexer->token_total);
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
		//data->cmd_table = initialize_command(data->lexer);
		add_history(data->line);
		free_data_except_env(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

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

// fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_TRNC, 0644);

// O_CREAT -> Cree le fichier si il existe pas.

// O_TRUNC -> Si le fiichier existe deja, il le vide.

// o_APPEND -> Ecris a la fin du fichier.
