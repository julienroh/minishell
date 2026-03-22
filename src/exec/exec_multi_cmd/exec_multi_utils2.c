/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:21:22 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/22 19:12:27 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*allocate env (list) in char ** format. if error, free data, v, exit. */

void	multi_init_envp(t_data *data, t_multi *v, char ***envp)
{
	*envp = NULL;
	*envp = env_to_envp(data->env);
	if (!*envp)
	{
		print_error("minishell : ");
		perror("malloc");
		free_exit_wrapper_child(data, v, 1);
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
