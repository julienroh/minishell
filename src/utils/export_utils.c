/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:08:03 by jroh              #+#    #+#             */
/*   Updated: 2026/01/24 17:05:30 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	already_in_struct(t_env *env, char *id, char *value, int plus)
{
	size_t	len;
	t_env	*tmp;

	tmp = env;
	len = ft_strlen(id);
	while (tmp)
	{
		if (ft_strncmp(tmp->id, id, len) == 0
			&& ft_strlen(tmp->id) == len && plus == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		else if (ft_strncmp(tmp->id, id, len) == 0
			&& ft_strlen(tmp->id) == len && plus == 1)
		{
			ft_strjoin(tmp->value, value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_identifier(char *id)
{
	int	i;

	i = 0;
	if (!id || ft_isdigit(id[0]))
		return (0);
	while (id[i])
	{
		if (i != 0 && id[i] == '+' && id[i + 1] == '=')
			return (2);
		else if (!ft_isalnum(id[i]) && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	add_end_value(t_env *env, char *id, char *value, int printable)
{
	t_env	*tmp;
	char	*old;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
			&& ft_strlen(tmp->id) == ft_strlen(id))
		{
			old = tmp->value;
			tmp->value = ft_strjoin(tmp->value, value);
			if (printable == 1)
				tmp->printable = 1;
			free(old);
			return ;
		}
		tmp = tmp->next;
	}
}

void	plus_equal_condition(t_env *env, char *str, int printable)
{
	int		i;
	char	*id;
	char	*value;
	t_env	*new;

	i = 0;
	id = NULL;
	value = NULL;
	while (str[i])
	{
		if (str[i] == '+')
		{
			id = ft_substr(str, 0, i);
			value = ft_strdup(str + i + 2);
			break ;
		}
		i++;
	}
	new = malloc(sizeof(t_env));
	if (!already_in_struct(env, id, value, 1))
	{
		new->id = id;
		new->value = value;
		if (printable == 1)
			new->printable = 1;
		else
			new->printable = 0;
		new->next = NULL;
		env_add_back(&env, new);
	}
	else
	{
		if (printable == 1)
			add_end_value(env, id, value, 1);
		else
			add_end_value(env, id, value, 0);
	}
}
