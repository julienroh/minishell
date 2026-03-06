/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:06:27 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/06 13:15:55 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin is_builtin(char *exec_argv)
{
	if (!exec_argv || !exec_argv[0])
		return (CMD);
	if (ft_strncmp(exec_argv, "cd", 3) == 0)
		return (CD);
	if (ft_strncmp(exec_argv, "pwd", 4) == 0)
		return (PWD);
	if (ft_strncmp(exec_argv, "export", 7) == 0)
		return (EXPORT);
	if (ft_strncmp(exec_argv, "env", 4) == 0)
		return (ENV);
	if (ft_strncmp(exec_argv, "echo", 5) == 0)
		return (ECHO);
	if (ft_strncmp(exec_argv, "unset", 6) == 0)
		return (UNSET);
	if (ft_strncmp(exec_argv, "exit", 6) == 0)
		return (EXIT);
	return(CMD);
}

int	exec_builtin_parent(char **exec_cmd, char **envp)
{
	//créer et adapté le format d'env en fonction du builtin ?
	//idée : transformer env en list, faire la cmd,
	// puis retransformer en envp(char**)
	//si besoin : return -1 error, 0 ok.
}

int	exec_external_cmd(t_data *data, t_exec_data *ctx)
{
	pid_t	pid;
	pid = safe_fork();
	if (pid == -1)
		return;
	if (pid == 0)
	{
		if (execve(ft_findpath(ctx->exec_argv[0]), ctx->exec_argv, ctx->envp) == -1)
		{
			perror("execve");
			data->last_status = 127;
		}
	}
	//close ?
	waitpid(pid, &data->last_status, 0);
	if (WIFEXITED(data->last_status))
		exit(WEXITSTATUS(data->last_status));
	if (WIFSIGNALED(data->last_status))
		exit(128 + WTERMSIG(data->last_status));
}