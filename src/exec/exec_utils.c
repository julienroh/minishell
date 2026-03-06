/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:41:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/06 13:07:53 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		perror("fork");
	return (pid);
}

void	close_all(int *pipefd, int fd_in, int fd_out)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_in);
	close(fd_out);
}


char	*find_shell_name(char **env)
{
	int		i;
	char	*p;

	i = 0;
	while (env && env[i])
	{
		p = ft_strnstr(env[i++], "SHELL=", 6);
		if (p)
			return (p + 6);
	}
	if (access("/bin/zsh", X_OK) == 0)
		return ("/bin/zsh");
	if (access("/bin/bash", X_OK) == 0)
		return ("/bin/bash");
	if (access("/bin/sh", X_OK) == 0)
		return ("/bin/sh");
	return (NULL);
}

