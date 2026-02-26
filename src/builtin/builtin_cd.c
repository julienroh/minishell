/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:23:06 by haoky             #+#    #+#             */
/*   Updated: 2026/02/26 15:19:01 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(t_env *env, char *id)
{
	char	*value;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
			&& ft_strlen(id) == ft_strlen(tmp->id))
		{
			value = tmp->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env_value(t_env *env, char *id, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
			&& ft_strlen(id) == ft_strlen(tmp->id))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

/*chdir is the function that make the computer change of directory. The rest of
our mission is to change (in the env struct) the value of PWD and OLDPWD.
*/

int	exec_cd(char **args, t_env *env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!args[1] || !ft_strncmp(args[1], "~", ft_strlen(args[1])))
		path = get_env_value(env, "HOME");
	else if (ft_strncmp(args[1], "-", ft_strlen(args[1])))
		path = get_env_value(env, "OLDPWD");
	else
		path = args[1];
	if (!path || chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	set_env_value(env, "OLDPWD", oldpwd);
	set_env_value(env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
