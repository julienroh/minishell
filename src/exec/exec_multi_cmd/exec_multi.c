/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:12:45 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/17 14:31:12 by haoky            ###   ########.fr       */
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

void	free_exit_wrapper_child(t_data *data, t_multi *v, int exit_int)
{
	free_all(data);
	free_structv(v);
	exit(exit_int);
}

static void	exec_multi_child(t_data *data, t_com *cmd, t_multi *v)
{
	char		**envp;
	char		*path;
	t_btn		type;
	int			code;

	type = is_builtin(cmd->argv[0]);
	child_setup_pipes(v, v->i, data);
	if (apply_redirections(cmd->redirs) == -1)
		free_exit_wrapper_child(data, v, 1);
	if (type != CMD)
	{
		data->last_status = exec_builtin_parent(data, cmd->argv);
		free_exit_wrapper_child(data, v, data->last_status);
	}
	multi_init_envp(data, v, &envp);
	code = multi_init_path(cmd, envp, &path);
	if (code != 0)
		free_exit_wrapper_child(data, v, code);
	if (execve(path, cmd->argv, envp) == -1)
	{
		print_error("minishell : ");
		perror(cmd->argv[0]);
		free_envp_path(envp, path);
		free_exit_wrapper_child(data, v, 127);
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
	int	sigint_printed;
	int	sigquit_printed;

	sigint_printed = 0;
	sigquit_printed = 0;
	i = 0;
	while (i < v->n_cmd)
	{
		waitpid(v->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			data->last_status = (WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
		{
			data->last_status = (128 + WTERMSIG(wstatus));
			if (WTERMSIG(wstatus) == SIGINT && sigint_printed == 0)
			{
				write(1, "\n", 1);
				sigint_printed = 1;
			}
			else if (WTERMSIG(wstatus) == SIGQUIT && sigquit_printed == 0)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				sigquit_printed = 1;
			}
		}
		i++;
	}
}

int	exec_multi_command(t_data *data, int n_cmd)
{
	t_multi	v;
	bool	is_last;
	t_com	*cmd;

	cmd = data->cmd_table;
	if (init_v(data, &v, n_cmd) == -1)
		return (-1);
	while (v.i < v.n_cmd)
	{
		is_last = is_last_cmd(n_cmd, v.i);
		if (spawn_child(&v) == -1)
			return (free_structv(&v), -1);
		if (v.pids[v.i] == 0)
		{
			signal_exec();
			exec_multi_child(data, cmd, &v);
		}
		wrapper_close_pipe_parent(&v, is_last);
		cmd = cmd->next;
		v.i++;
	}
	wait_multi_pids(&v, data);
	return (free_structv(&v), 0);
}
