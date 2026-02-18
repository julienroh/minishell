/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:28:15 by jroh              #+#    #+#             */
/*   Updated: 2026/02/18 17:45:06 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_size(t_env *env)
{
	int	i;
	t_env *current;

	i = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

static void	sort_char_env(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_strncmp(args[j], args[i]), max(args[j], args[i]))
		}
	}
}

void	only_export(t_env *env)
{
	int		i;
	int		size;
	char	**char_env;
	t_env	*current;
	
	i = 0;
	current = env;
	size = define_size(env);
	char_env = malloc(sizeof(char) * size + 1);
	while (current != NULL)
	{
		char_env[i] = current->id;
		i++;
		current = current->next;
	}
	sort_char_env(char_env);
}
