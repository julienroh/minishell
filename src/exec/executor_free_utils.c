/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_free_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:12:44 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/04 23:54:03 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **array)
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
void	free_env_list(t_env *env)
{
	t_env *tmp;
	t_env *cur;

	if (!env)
		return ;
	cur = env;
	while(cur)
	{
		tmp = cur;
		free(tmp->id);
		tmp->id = NULL;
		free(tmp->value);
		tmp->value = NULL;
		cur = tmp->next;
		free(tmp);
	}
}
void wrapper_free_single_command(t_exec_data *ctx)
{
	free_double_array(ctx->envp);
	free_env_list(ctx->fake_env);
}
