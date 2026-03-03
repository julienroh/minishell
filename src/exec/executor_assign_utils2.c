/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_assign_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:18:01 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/03 22:45:41 by mfumeaux         ###   ########.fr       */
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

bool	is_only_assignment_no_cmd(char **argv, int assign_count)
{
	//uniquement des assign dans mon argv, pas de vrai cmds.
	if (!argv)
		return (false);
	if (argv[assign_count] == NULL)
		return (true);
	return (false);
}

int	apply_prefix_assignments(t_env **env, char **argv, int assign_count)
{
	int	i;
	
	if (!env || !argv)
		return (-1);
	i = 0;
	while(i < assign_count)
	{
		if (apply_one_assignment(env, argv[i++]) == -1)
			return (-1);
	}
	print_list_env(*env); //debug list.
	return (0);
}