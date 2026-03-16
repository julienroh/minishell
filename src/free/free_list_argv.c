/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:42:14 by haoky             #+#    #+#             */
/*   Updated: 2026/03/16 11:15:52 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_argv(t_argv *list_argv)
{
	t_argv	*current;
	t_argv	*tmp;

	current = list_argv;
	while (current != NULL)
	{
		tmp = current->next;
		free(current->arg);
		free(current);
		current = tmp;
	}
}

void	free_list_argv(t_command *cmd)
{
	t_command	*current;

	current = cmd;
	while (current != NULL)
	{
		free_argv(current->list_argv);
		current = current->next;
	}
}
