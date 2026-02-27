/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_free_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:12:44 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/02/27 14:24:56 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_double_array(char **array)
{
	int	i;

	i = 0;

	if (!array)
		return ;
	while(array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

static void	free_list_redirs(t_redir *headptr)
{
	t_redir	*redir;
	t_redir	*next_redir;

	redir = headptr;
	while (redir)
	{
		next_redir = redir->next;
		free(redir->target);
		redir->target = NULL;
		free(redir);
		redir = next_redir;
	}
}

void	free_cmdtable(t_data *data)
{
	t_command	*cmd_table;
	t_command	*next_cmd;

	if (!data)
		return;
	cmd_table = data->cmd_table;
	while(cmd_table)
	{
		next_cmd = cmd_table->next;
		// free de argv
		free_double_array(cmd_table->argv);
		cmd_table->argv = NULL;
		//free des redirs
		free_list_redirs(cmd_table->redirs);
		cmd_table->redirs = NULL;
		free(cmd_table);
		cmd_table = next_cmd;
	}
	data->cmd_table = NULL;
}

