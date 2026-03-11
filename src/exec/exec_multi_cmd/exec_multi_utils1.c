/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:38:51 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/11 21:59:25 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_filled_int_array(int **array, int filled)
{
	int	i;

	i = 0;
	while (i < filled)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int  init_pipes(t_multi *v, int n_cmd)
{
	int i;

	i = 0;
	while (i < n_cmd - 1)
	{
		if (pipe(v->pipefd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int init_v(t_data *data, t_multi *v, int n_cmd)
{
	int	i;

	i = 0;
	v->i = 0;
	v->n_cmd = n_cmd;
	v->pids = malloc(sizeof(pid_t) * n_cmd);
	if (!v->pids)
		return (perror("malloc"), data->last_status = 1, -1);
	v->pipefd = malloc(sizeof(int *) * (n_cmd - 1));
	if (!v->pipefd)
		return (perror("malloc"), free(v->pids), data->last_status = 1, -1);
	while(i < n_cmd - 1)
	{
		v->pipefd[i] = malloc(sizeof(int) * 2);
		if (!v->pipefd[i])
			return (perror("malloc"), free_filled_int_array(v->pipefd, i), 
					free(v->pids), data->last_status = 1, -1);
		i++;
	}
	if (init_pipes(v, n_cmd) == -1)
	{
		free_filled_int_array(v->pipefd, i);
		return (perror("pipe"),  free(v->pids), data->last_status = 1, -1);
	}
	return (0);
}

int	spawn_child(t_multi *v)
{
	v->pids[v->i] = fork();
	if (v->pids[v->i] == -1)
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

bool	is_last_cmd(int cmdnumber, int i)
{
	if (i == (cmdnumber - 1))
		return (true);
	else
		return (false);
}
