/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:08:16 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/22 17:25:42 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return a pointer beginning right after PATH= of envp.
static char	*get_path_value(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/* makes a string which joins cmd (ls for example) to the path
For example > /home/bin/ls  */

static char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	if (dir[0] == '\0')
		dir = ".";
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

//if slash found, test path accesses. return correct code if error.
static int	tests_path_slash(char **out_path, char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (127);
	if (is_directory(cmd))
		return (errno = EISDIR, 126);
	if (access(cmd, X_OK) != 0)
		return (126);
	*out_path = ft_strdup(cmd);
	if (!*out_path)
		return (1);
	return (0);
}

/* if return = 0, the cmd is found, outpath is set and dirs is freed.
if return == 1, it's a malloc error. outpath is NULL
if return == 127, it's impossible to find the cmd in path.*/
static int	find_command_in_path(char **dirs, char **out_path, char *cmd)
{
	char	*candidate;
	int		i;
	int		code;

	i = 0;
	code = 127;
	while (dirs[i])
	{
		candidate = join_path(dirs[i], cmd);
		if (!candidate)
			return (free_double_array(dirs), 1);
		if (access(candidate, F_OK) == 0)
		{
			if (access(candidate, X_OK) == 0 && !is_directory(candidate))
				return (free_double_array(dirs), *out_path = candidate, 0);
			code = 126;
		}
		free(candidate);
		i++;
	}
	return (free_double_array(dirs), errno = ENOENT, code);
}

/* solve if path is absolute or relative. test the access of the commands. 
return correct error if needed.
*/

int	ft_findpath(char **out_path, char *cmd, char **envp)
{
	char	*path_value;
	char	**dirs;
	int		code;

	code = 0;
	if (!out_path || !cmd || cmd[0] == '\0')
		return (127);
	*out_path = NULL;
	if (ft_strchr(cmd, '/'))
		return (tests_path_slash(out_path, cmd));
	path_value = get_path_value(envp);
	if (!path_value || path_value[0] == '\0')
		return (127);
	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (1);
	code = find_command_in_path(dirs, out_path, cmd);
	return (code);
}
