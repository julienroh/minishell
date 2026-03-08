/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:08:16 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/08 21:05:00 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//renvoie un pointeur débutant juste après PATH= de l'envp.
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

//test si c'est un dossier. stat remplis la struct, si dossier return 1, sinon return 0.
static int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

//construit une string qui joint la cmd (ls mettons) au path. (/home/bin/ls p.e.)
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

//Si slash trouvé, test les accès au path. 
static int tests_path_slash(char **out_path, char *cmd)
{
		if (access(cmd, F_OK) != 0)
			return (127);
		if (is_directory(cmd))
			return (126);
		if (access(cmd, X_OK) != 0)
			return (126);
		*out_path = ft_strdup(cmd);
		if (!*out_path)
			return (1);
		return (0);
}

int	find_command_in_path(char **dirs, char *candidate, char **out_path, char *cmd)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		candidate = join_path(dirs[i], cmd);
		if (!candidate)
			return (free_double_array(dirs), 1);
		if (access(candidate, X_OK) == 0 && !is_directory(candidate))
			return (free_double_array(dirs), *out_path = candidate, 0);
		free(candidate);
		i++;
	}
	return (free_double_array(dirs), 127);
}

/* Résout path absolute et relatif. Teste aussi si accès à la commande ok. 
/!\ retourne toujours un malloc, car il y a un free qui vient derrière.
*/
int	ft_findpath(char **out_path, char *cmd, char **envp)
{
	char	*path_value;
	char	**dirs;
	char	*candidate;
	int		i;

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
	i = 0;
	//Réduire ici, check find_command_in_path en haut, c'est pas propre.
	while (dirs[i])
	{
		candidate = join_path(dirs[i], cmd);
		if (!candidate)
			return (free_double_array(dirs), 1);
		if (access(candidate, X_OK) == 0 && !is_directory(candidate))
			return (free_double_array(dirs), *out_path = candidate, 0);
		free(candidate);
		i++;
	}
	free_double_array(dirs);
	return (127);
}

//exemple au split de dirs : 
// /home/swagy/.local/bin
// /usr/local/sbin
// /usr/local/bin
// /usr/sbin
// /usr/bin
// /sbin
// /bin
// /usr/games
// /usr/local/games
// /snap/bin
// /home/swagy/.local/bin
