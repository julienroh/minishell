/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:42:14 by haoky             #+#    #+#             */
/*   Updated: 2026/03/12 08:30:36 by haoky            ###   ########.fr       */
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
		//current->list_argv = NULL;
		current = current->next;
	}
}
