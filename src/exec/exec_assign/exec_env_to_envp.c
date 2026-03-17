/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_to_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:12:44 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/17 17:29:17 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
Construit la string "KEY=VALUE" pour un node.
Si value == NULL, construit "KEY=" (au lieu de planter).
*/

static char	*env_node_to_line(t_env *node)
{
	char	*tmp;
	char	*line;

	if (!node || !node->id)
		return (NULL);
	if (!node->value)
		return (ft_strjoin(node->id, "="));
	tmp = ft_strjoin(node->id, "=");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(tmp, node->value);
	free(tmp);
	return (line);
}

/*
Libère partiellement un envp[] si une allocation échoue pendant sa construction.
*/

static void	free_envp_partial(char **envp, int filled)
{
	while (filled > 0)
	{
		filled--;
		free(envp[filled]);
	}
	free(envp);
}

/*
Convertit une liste t_env en char **envp pour execve.
Retourne NULL en cas d'erreur malloc.
*/
char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	char	*line;

	envp = malloc(sizeof(char *) * (env_list_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->printable == 1 && env->value != NULL)
		{
			line = env_node_to_line(env);
			if (!line) 
			{
				free_envp_partial(envp, i);
				return (NULL);
			}
			envp[i] = line;
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
