/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_except_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:54:56 by jroh              #+#    #+#             */
/*   Updated: 2026/03/02 18:22:01 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	free_lexer(t_lexer *lexer)
{
	int		i;
	t_part	*current;
	t_part	*next;

	if (!lexer || !lexer->tokens)
		return ;
	i = 0;
	while (i < lexer->token_total)
	{
		current = lexer->tokens[i].parts;
		while (current != NULL)
		{
			next = current->next;
			free(current->value);
			free(current);
			current = next;
		}
		free(lexer->tokens[i].value);
		i++;
	}
	free(lexer->tokens);
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*current;
	t_redir	*next;

	current = redirs;
	while (current != NULL)
	{
		next = current->next;
		free(current->target);
		free(current);
		current = next;
	}
}

static void	free_cmd(t_command *cmd)
{
	t_command	*current;
	t_command	*next;

	if (!cmd)
		return ;
	current = cmd;
	while (current != NULL)
	{
		next = current->next;
		free_args(current->argv);
		free_redirs(current->redirs);
		free(current);
		current = next;
	}
}

void	free_data_except_env(t_data *data)
{
	if (!data)
		return ;
	free(data->line);
	free_args(data->args);
	free_lexer(data->lexer);
	free(data->lexer);
	free_cmd(data->cmd_table);
}
