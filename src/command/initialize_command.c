/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:12:05 by jroh              #+#    #+#             */
/*   Updated: 2026/03/12 10:14:32 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_list_argv(t_argv **list_argv, t_data *data, char *value)
{
	t_argv	*current;
	t_argv	*new;

	new = malloc(sizeof(t_argv));
	if (!new)
		free_all_malloc(data);
	new->arg = ft_strdup(value);
	if (!new->arg)
	{
		free(new);
		free_all_malloc(data);
	}
	new->next = NULL;
	if (*list_argv == NULL)
	{
		*list_argv = new;
		return ;
	}
	current = *list_argv;
	while (current->next)
		current = current->next;
	current->next = new;
}

static t_command	*create_command(t_data *data)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		free_all_malloc(data);
	cmd->list_argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	process_token(t_data *data, t_lexer *lex, t_command **curr, int *i)
{
	if (lex->tokens[*i].type == PIPE)
	{
		(*curr)->next = create_command(data);
		*curr = (*curr)->next;
		(*i)++;
	}
	else if (is_redir(&lex->tokens[*i]))
	{
		add_redir(&(*curr)->redirs, data, *i, lex->tokens[*i + 1].value);
		*i += 2;
	}
	else
	{
		add_list_argv(&(*curr)->list_argv, data, lex->tokens[*i].value);
		(*i)++;
	}
}

t_command	*initialize_command(t_data *data, t_lexer *lexer)
{
	t_command	*head;
	t_command	*current;
	int			i;

	i = 0;
	head = create_command(data);
	current = head;
	while (i < lexer->token_total)
		process_token(data, lexer, &current, &i);
	from_list_to_array(data, head);
	free_list_argv(head);
	return (head);
}
