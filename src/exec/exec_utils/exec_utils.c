/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:41:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/13 22:22:59 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_execve_error(t_data *data, char **envp, char *path)
{
		ft_putstr_fd("minishell : ", 2);
		perror(data->cmd_table->argv[0]);
		free_all(data);
		free_envp_path(envp, path);
		exit(127);
}

void	close_if_valid(int fd)
{
	if (fd >= 0)
		close(fd);
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("fork");
	}
	return (pid);
}

