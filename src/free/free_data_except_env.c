/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_except_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:54:56 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 15:19:53 by jroh             ###   ########.fr       */
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

static void	free_cmd(t_com *cmd)
{
	t_com	*current;
	t_com	*next;

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
	data->line = NULL;
	free_lexer(data->lexer);
	free(data->lexer);
	data->lexer = NULL;
	free_cmd(data->cmd_table);
	data->cmd_table = NULL;
}
