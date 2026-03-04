/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:12:05 by jroh              #+#    #+#             */
/*   Updated: 2026/03/04 15:05:34 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_last_pipe(t_lexer *lexer)
{
	int	i;
	int	last_pipe;

	i = 0;
	last_pipe = 0;
	while (i < lexer->token_total)
	{
		if (lexer->tokens[i].type == PIPE)
			last_pipe = i;
		i++;
	}
	return (last_pipe);
}

static t_redir_type	define_type_redir(t_data *data, int i)
{
	if (data->lexer->tokens[i].type == T_IN)
		return (R_IN);
	if (data->lexer->tokens[i].type == T_OUT)
		return (R_OUT);
	if (data->lexer->tokens[i].type == T_APPEND)
		return (R_APPEND);
	if (data->lexer->tokens[i].type == T_HEREDOC)
		return (R_HEREDOC);
	return (0);
}

static void	add_redir(t_redir *redir, t_data *data, int i)
{
	t_redir	*current;
	t_redir	*next;

	printf("pouet31\n");
	if (!redir)
	{
		redir->type = define_type_redir(data, i);
		redir->target = ft_strdup(data->lexer->tokens[i + 1].value);
		redir->next = NULL;
		if (!redir->target)
			free_all(data);
		return ;
	}
	next = malloc(sizeof(t_redir));
	if (!next)
		free_all(data);
	current = redir;
	while (current->next == NULL)
		current = current->next;
	next->type = define_type_redir(data, i);
	next->target = ft_strdup(data->lexer->tokens[i + 1].value);
	next->next = NULL;
	if (!next->target)
		free_all(data);
	current->next = next;
	printf("pouet3\n");
}

static void	add_list_argv(t_argv *list_argv, t_data *data, int i)
{
	t_argv	*current;
	t_argv	*next;

	printf("pouet21\n");
	next = malloc(sizeof(t_argv));
	if (list_argv)
		printf("arg = %s\n", list_argv->arg);
	if (!list_argv)
	{
		printf("value = %s\n", data->lexer->tokens[i].value);
		next->arg = ft_strdup(data->lexer->tokens[i].value);
		printf("non\n");
		if (!next->arg)
		free_all(data);
	next->next = NULL;
	current = next;
	return ;
	}
	current = list_argv;
	while (current->next != NULL)
		current = current->next;
	printf("test\n");
	next->arg = ft_strdup(data->lexer->tokens[i].value);
	printf("test\n");
	next->next = NULL;
	if (!next->arg)
		free_all(data);
	current->next = next;
	printf("pouet2\n");
}

static void	create_command(t_command *command, t_data *data, int start, int i)
{
	t_command	*current;
	t_command	*next;

	next = malloc(sizeof(t_command));
	if (!next)
		free_all(data);
	current = command;
	while (current->next != NULL)
		current = current->next;
	while (start < i)
	{
		if (is_redir(&data->lexer->tokens[i]) == 1)
		{
			add_redir(next->redirs, data, i);
			start++;
		}
		else if (start < i)
			add_list_argv(next->list_argv, data, i);
		start++;
	}
	current->next = next;
	printf("pouet1\n");
}

t_command	*initialize_command(t_data *data, t_lexer *lexer)
{
	t_command	*command;
	int			i;
	int			start;
	int			last_pipe;

	i = 0;
	last_pipe = find_last_pipe(lexer);
	command = malloc(sizeof(t_command));
	if (!command)
		free_all(data);
	command->list_argv = NULL;
	command->redirs = NULL;
	command->next = NULL;
	while (i < lexer->token_total)
	{
		start = i;
		if (lexer->tokens[i].type == PIPE)
			create_command(command, data, start, i);
		i++;
	}
	if (last_pipe == 0)
		create_command(command, data, 0, i);
	else
		create_command(command, data, last_pipe, i);
	printf("pouet final\n");
	return (command);
}
