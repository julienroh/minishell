/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:56:31 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/06 13:08:37 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (cmd); //a revoir ? 
	else if ((slash_found == true && access(cmd, X_OK) == -1))
		return (NULL); // add perror ?
	while (env[i])
	{
		path = ft_strnstr(env[i++], "PATH=", 6); // 6 ? pas 5 ? 
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
