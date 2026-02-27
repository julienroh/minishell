/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/02/27 12:31:56 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fakecmdtable(t_data *data)
{
	int	i;
	t_redir	*redir;
	t_redir	*nxt_redir;

	i = 0;
	// free de argv
	while(data->cmd_table->argv[i])
	{
		free(data->cmd_table->argv[i]);
		data->cmd_table->argv[i++] = NULL;
	}
	free(data->cmd_table->argv);
	data->cmd_table->argv = NULL;

	//free des redirs
	redir = data->cmd_table->redirs;
	while (redir)
	{
		nxt_redir = redir->next;
		free(redir->target);
		redir->target = NULL;
		free(redir);
		redir = nxt_redir;
	}
	data->cmd_table->redirs = NULL;
	//add free next node certainement.
	free(data->cmd_table);
	data->cmd_table = NULL;
}

void	fake_cmdtable(t_data *data)
{
	data->cmd_table = malloc(sizeof(t_command));
	data->cmd_table->argv = malloc(sizeof(char *) * 3);
	data->cmd_table->argv[0] = ft_strdup("grep");
	data->cmd_table->argv[1] = ft_strdup("hi");
	data->cmd_table->argv[2] = NULL;
	data->cmd_table->next = NULL;
	data->cmd_table->redirs = NULL;
}

void	executor_run(t_data *data)
{
	
}

int main(int ac, char **av, char **env)
{
	t_data data;
	fake_cmdtable(&data);
	executor_run(&data);

}