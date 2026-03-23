/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:38:51 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/23 09:41:34 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_v(t_data *data, t_multi *v, int n_cmd)
{
	v->i = 0;
	v->n_cmd = n_cmd;
	v->prev_fd = -1;
	v->cmd = data->cmd_table;
	v->is_last = false;
	v->pids = malloc(sizeof(pid_t) * n_cmd);
	if (!v->pids)
		return (ft_putstr_fd("minishell : ", 2),
			perror("malloc"), data->last_status = 1, -1);
	return (0);
}

bool	is_last_cmd(int cmdnumber, int i)
{
	if (i == (cmdnumber - 1))
		return (true);
	else
		return (false);
}

int	abort_fork_failed(t_multi *v, t_data *data)
{
	close_pipes(v);
	v->n_cmd = v->i;
	wait_multi_pids(v, data);
	free(v->pids);
	return (-1);
}

/*Exec builtins in multi cmds scenarios*/
void	builtin_in_multi_exec(t_data *data, t_multi *v, t_btn type, t_com *cmd)
{
	if (type == EXIT)
	{
		free(v->pids);
		v->pids = NULL;
	}
	data->last_status = exec_builtin_parent(data, cmd->argv);
	free_exit_wrapper_child(data, v, data->last_status);
}
