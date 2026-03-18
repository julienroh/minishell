/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:11:26 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/18 12:58:32 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Take the exit status and update data->last_status with the correct number.
*/

void	wait_pid_signaled(t_data *data, int wstatus,
		int *sigint_printed, int *sigquit_printed)
{
	data->last_status = (128 + WTERMSIG(wstatus));
	if (WTERMSIG(wstatus) == SIGINT && *sigint_printed == 0)
	{
		write(1, "\n", 1);
		*sigint_printed = 1;
	}
	else if (WTERMSIG(wstatus) == SIGQUIT && *sigquit_printed == 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		*sigquit_printed = 1;
	}
}

/* Wrapper to exit in child. The goal is to prevent leaks.
*/

void	free_exit_wrapper_child(t_data *data, t_multi *v, int exit_int)
{
	free_all(data);
	free_structv(v);
	exit(exit_int);
}

/* Checks for errors in path. */

int	multi_init_path(t_com *cmd, char **envp, char **path)
{
	int	code;

	*path = NULL;
	code = ft_findpath(path, cmd->argv[0], envp);
	if (code != 0)
	{
		if (!ft_strchr(cmd->argv[0], '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			if (*cmd->argv[0] == '\0')
				ft_putstr_fd(": command not found\n", 2);
			else
				ft_putstr_fd(" :command not found\n", 2);
			free_envp_path(envp, *path);
			return (code);
		}
		ft_putstr_fd("minishell : ", 2);
		perror(cmd->argv[0]);
		free_envp_path(envp, *path);
		return (code);
	}
	return (code);
}
