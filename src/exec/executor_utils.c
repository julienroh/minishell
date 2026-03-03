/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:41:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/03 16:32:46 by mfumeaux         ###   ########.fr       */
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
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	close_all(int *pipefd, int fd_in, int fd_out)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_in);
	close(fd_out);
}

char	*ft_find_path(char *cmd, char **env)
{
	bool	slash_found;
	int		i;
	char	*path;

	i = 0;
	slash_found = false;
	if (ft_strchr(cmd, '/') != NULL)
		slash_found = true;
	if (slash_found == true && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else if ((slash_found == true && access(cmd, X_OK) == -1))
		return (NULL);
	while (env[i])
	{
		path = ft_strnstr(env[i++], "PATH=", 6);
		if (path != NULL)
			break ;
	}
	path = ft_folder_access_test(path, cmd);
	return (path);
}

char	*ft_folder_access_test(char *path, char *cmd)
{
	char	**folders;
	char	*full_path;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (ft_strncmp(path, "PATH=", 5) == 0)
		path += 5;
	folders = ft_split(path, ':');
	while (folders[i])
	{
		str = ft_strjoin(folders[i++], "/");
		if (!str)
			break ;
		full_path = ft_strjoin(str, cmd);
		free(str);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (free_double_array(folders), full_path);
		free(full_path);
	}
	return (free_double_array(folders), NULL);
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

