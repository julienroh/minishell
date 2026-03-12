/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:09:47 by haoky             #+#    #+#             */
/*   Updated: 2026/03/12 10:14:32 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_redir(t_redir **redir, t_data *data, int i, char *target)
{
	t_redir	*current;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		free_all_malloc(data);
	new->type = define_type_redir(data, i);
	new->target = ft_strdup(target);
	new->next = NULL;
	if (*redir == NULL)
	{
		*redir = new;
		return ;
	}
	current = *redir;
	while (current ->next)
		current = current->next;
	current->next = new;
}

static int	count_list_argv(t_argv *list_argv)
{
	t_argv	*current;
	int		count;

	count = 0;
	current = list_argv;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

static char	**create_cmd_argv(t_data *data, t_argv *list_argv)
{
	t_argv	*current;
	char	**argv;
	int		number;
	int		i;

	i = 0;
	number = count_list_argv(list_argv);
	argv = malloc(sizeof(char *) * (number + 1));
	if (!argv)
		free_all_malloc(data);
	current = list_argv;
	while (current != NULL)
	{
		argv[i] = ft_strdup(current->arg);
		if (!argv[i])
			free_all_malloc(data);
		i++;
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	from_list_to_array(t_data *data, t_command *head)
{
	t_command	*current;

	current = head;
	while (current != NULL)
	{
		current->argv = create_cmd_argv(data, current->list_argv);
		current = current->next;
	}
}
