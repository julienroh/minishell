/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:12:45 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/12 15:04:17 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_structv(t_multi *v)
{
	int	i;

	i = 0;
	free(v->pids);
	while (i < v->n_cmd - 1)
	{
		free(v->pipefd[i]);
		i++;
	}
	free(v->pipefd);
	
}

static void	exec_multi_child(t_data *data, t_command *cmd, t_multi *v)
{
	char 		**envp;
	char		*path;
	t_builtin	type;

	type = is_builtin(cmd->argv[0]);
	child_setup_pipes(v, v->i);
	if (apply_redirections(cmd->redirs) == -1)
	{
		free_all(data);
		free_structv(v);
		exit(1);
	}

	if (type != CMD)
	{
		exec_builtin_parent(data, cmd->argv);
		free_all(data);
		free_structv(v);
		exit(data->last_status);
	}
	multi_init_path_envp_cmd(cmd, data, &envp, &path);
	if (execve(path, cmd->argv, envp) == -1)
	{	
		perror(cmd->argv[0]);
		free_all(data);
		free_structv(v);
		free_envp_path(envp, path);
		exit(127);
	}
}

static void	wrapper_close_pipe_parent(t_multi *v, bool is_last)
{
	if (is_last == false)
		close(v->pipefd[v->i][1]);
	if (v->i > 0)
		close(v->pipefd[v->i - 1][0]);
}

static void	wait_multi_pids(t_multi *v, t_data *data)
{
	int	i;
	int	wstatus;
	
	i = 0;
	while(i < v->n_cmd)
	{
		waitpid(v->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			data->last_status = (WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
			data->last_status = (128 + WTERMSIG(wstatus));
		i++;
	}
}

int   exec_multi_command(t_data *data, int n_cmd)
{
	t_multi		v;
	bool		is_last;
	t_command	*cmd;

	cmd = data->cmd_table;
	if (init_v(data, &v, n_cmd) == -1)
		return (-1);
	while (v.i < v.n_cmd)
	{
		is_last = is_last_cmd(n_cmd, v.i);
		if (spawn_child(&v) == -1)
			return (free_structv(&v), -1);
		if (v.pids[v.i] == 0)
			exec_multi_child(data, cmd, &v);
		wrapper_close_pipe_parent(&v, is_last);
		cmd = cmd->next;
		v.i++;
		//sigaction.
	}
	wait_multi_pids(&v, data);
	return (free_structv(&v), 0);
}
