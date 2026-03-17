/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:28:15 by jroh              #+#    #+#             */
/*   Updated: 2026/03/17 15:41:09 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_value(char *id, t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strlen(current->id) == ft_strlen(id)
			&& ft_strncmp(current->id, id, ft_strlen(id)) == 0)
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

static void	wrapper_only_export(t_data *data, char **char_env)
{
	sort_char_env(char_env);
	print_export(char_env, data->env);
	free_char_env(char_env);
}

int	only_export(t_data *data, int i)
{
	int		size;
	char	**char_env;
	t_env	*current;

	current = data->env;
	size = define_size(data->env);
	char_env = malloc(sizeof(char *) * (size + 1));
	if (!char_env)
		free_all_malloc(data);
	while (current != NULL)
	{
		char_env[i] = ft_strdup(current->id);
		if (!char_env[i])
		{
			while (i-- > 0)
				free(char_env[i]);
			free(char_env);
			free_all_malloc(data);
		}
		i++;
		current = current->next;
	}
	char_env[i] = NULL;
	wrapper_only_export(data, char_env);
	return (0);
}
