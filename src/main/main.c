/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/01/23 14:46:50 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit(char *line)
{
	if (!line)
	{
		print_exit(line);
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
	return (1);
}

static void	waiting_function(t_env *env)
{
	char	*line;
	char	**args;
	t_lexer	*lexer;

	while (1)
	{
		line = readline("minishell$ ");
		if (check_exit(line))
			break ;
		if (is_blank_line(line))
		{
			free(line);
			continue ;
		}
		lexer = lexer_parse_line(line);
		args = lexer_expand_to_args(lexer, env);
		if (!analyze_args(args, env))
		{
			print_exit(line);
			break ;
		}
		add_history(line);
		free(args);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_struct;

	(void)argc;
	(void)argv;
	env_struct = parser_env(env);
	if (!env_struct)
	{
		print_error("Out of memory\n");
		exit(1);
	}
	waiting_function(env_struct);
	return (0);
}
