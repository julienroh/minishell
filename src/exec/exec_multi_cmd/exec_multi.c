/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:12:45 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/21 20:24:22 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pipes_handling(t_multi *v)
{
	if (v->prev_fd != -1)
	{
		dup2(v->prev_fd, STDIN_FILENO);
		close(v->prev_fd);
	}
	if (v->is_last == false)
	{
		dup2(v->pipefd[1], STDOUT_FILENO);
		close(v->pipefd[1]);
		close(v->pipefd[0]);
	}
}

static void	exec_multi_child(t_data *data, t_com *cmd, t_multi *v)
{
	char		**envp;
	char		*path;
	t_btn		type;
	int			code;

	type = is_builtin(cmd->argv[0]);
	child_pipes_handling(v);
	if (apply_redirections(cmd->redirs) == -1)
		free_exit_wrapper_child(data, v, 1);
	if (type != CMD)
	{
		data->last_status = exec_builtin_parent(data, cmd->argv);
		free_exit_wrapper_child(data, v, data->last_status);
	}
	multi_init_envp(data, v, &envp);
	code = multi_init_path(cmd, envp, &path); //check pathing.
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
			data->last_status = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
			wait_pid_signaled(data, wstatus, &sigint_printed, &sigquit_printed);
		i++;
	}
}

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("pipe");
		return (-1);
	}
	return (0);
}
void	close_pipes(t_multi *v)
{
	if (v->is_last == false)
	{
		close(v->pipefd[0]);
		close(v->pipefd[1]);
	}
	if (v->prev_fd != -1)
		close(v->prev_fd);
}

int	safe_fork_multi(t_multi *v)
{
	v->pids[v->i] = fork();
	if (v->pids[v->i] == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("fork");
		return (-1);
	}
	return (0);
}
int	abort_pipe_failed(t_multi *v, t_data *data)
{
	if (v->prev_fd != -1)
		close(v->prev_fd);
	v->n_cmd = v->i;
	wait_multi_pids(v, data);
	free(v->pids);
	return (-1);
}

int	abort_fork_failed(t_multi *v, t_data *data)
{
	close_pipes(v);
	v->n_cmd = v->i;
	wait_multi_pids(v, data);
	free(v->pids);
	return (-1);
}

int	exec_multi_command(t_data *data, int n_cmd)
{
	t_multi	v;

	if (init_v(data, &v, n_cmd) == -1)
		return (-1);
	while (v.i < v.n_cmd)
	{
		v.is_last = is_last_cmd(n_cmd, v.i);
		if (v.is_last == false && create_pipe(v.pipefd) == -1)
			return (abort_pipe_failed(&v, data));
		if (safe_fork_multi(&v) == -1)
			return (abort_fork_failed(&v, data)); //free struct qqch ? 	
		if (v.pids[v.i] == 0)
		{
			signal_exec();
			exec_multi_child(data, v.cmd, &v);
		}
		if (v.prev_fd != -1)
			close(v.prev_fd);
		if (v.is_last == false)
		{
			v.prev_fd = v.pipefd[0];
			close(v.pipefd[1]);
		}
		v.cmd = v.cmd->next;
		v.i++;
	}
	wait_multi_pids(&v, data);
	return (free(v.pids), 0); //a faire encore FREE QUOI = avant c'était free structv.
}

