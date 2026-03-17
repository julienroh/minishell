/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:18:01 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/17 16:37:54 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_malloc_ok(char *str)
{
	if (!str)
	{
		perror("malloc");
		return (1);
	}
	return (0);
}
//check de malloc pour un str. renvoie 0 si tout est ok.

t_env	*lst_env_new(char *name, char *value)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->id = NULL;
	new->value = NULL;
	new->next = NULL;
	new->printable = 0;
	new->id = ft_strdup(name);
	if (!new->id)
		return (free(new), NULL);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new->id), free(new), NULL);
	return (new);
}
//crée et init une node d'env.

void	lst_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
//ajoute une node dans ma list d'env.

bool	is_only_assignment_no_cmd(char **argv, int assign_count)
{
	if (!argv)
		return (false);
	if (argv[assign_count] == NULL)
		return (true);
	return (false);
}
	//uniquement des assign dans mon argv, pas de vrai cmds.

int	apply_prefix_assignments(t_env **env, char **argv, int assign_count)
{
	int	i;

	if (!env || !argv)
		return (-1);
	i = 0;
	while (i < assign_count)
	{
		if (apply_one_assignment(env, argv[i++]) == -1)
			return (-1);
	}
	return (0);
}
	//pour chaque prefix dans ma cmd, les appliques dans env ou fakenv.