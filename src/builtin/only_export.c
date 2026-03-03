/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:28:15 by jroh              #+#    #+#             */
/*   Updated: 2026/03/02 18:31:01 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_size(t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

static char	*find_value(char *id, t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strncmp(current->id, id, max(current->id, id)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static void	print_export(char **char_env, t_env *env)
{
	int		i;
	char	*value;

	i = 0;
	while (char_env[i])
	{
		value = find_value(char_env[i], env);
		printf("export %s=\"%s\"\n", char_env[i], value);
		i++;
	}
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
			if (ft_strncmp(args[j], args[i], max(args[j], args[i]) < 0))
				swap(&args[j], &args[i]);
			j++;
		}
		i++;
	}
}

void	only_export(t_data *data)
{
	int		i;
	int		size;
	char	**char_env;
	t_env	*current;

	i = -1;
	current = data->env;
	size = define_size(data->env);
	char_env = malloc(sizeof(char *) * (size + 1));
	if (!char_env)
		free_all(data);
	while (current != NULL)
	{
		char_env[++i] = ft_strdup(current->id);
		if (!char_env[i])
		{
			free_char_env(char_env);
			free_all(data);
		}
		current = current->next;
	}
	char_env[i] = NULL;
	sort_char_env(char_env);
	print_export(char_env, data->env);
	free_char_env(char_env);
}
