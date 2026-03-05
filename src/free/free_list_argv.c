/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:42:14 by haoky             #+#    #+#             */
/*   Updated: 2026/03/05 16:46:06 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_argv(t_argv *list_argv)
{
	t_argv	*current;

	current = list_argv;
	while (current != NULL)
	{
		free(current->arg);
		current = current->next;
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
