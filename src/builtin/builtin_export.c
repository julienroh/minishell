/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:11:40 by haoky             #+#    #+#             */
/*   Updated: 2026/03/18 12:13:51 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_id_value(char *id, char *value)
{
	free(id);
	free(value);
}

static void	add_in_env(t_data *data, char **args, int i, int printable)
{
	t_env	*new;

	new = env_new(data, args[i + 1]);
	new->printable = printable;
	env_add_back(&data->env, new);
}

static void	check_if_exist(t_data *data, t_env *env, char **args, int i)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, args[i + 1], ft_strlen(args[i + 1]))
			&& (ft_strlen(tmp->id) == ft_strlen(args[i + 1])))
		{
			tmp->printable = 1;
			return ;
		}
		tmp = tmp->next;
	}
	add_in_env(data, args, i, 0);
}


/*Check if the id already exist, if that's the case, we only replace the old
value by the new one. If not, we create a new space for the new id and value.
*/

int	exec_export(t_data *data, char **args, int i)
{
	char	*id;
	char	*value;

	if (!args[1])
		return (only_export(data, 0));
	while (args[i + 1])
	{
		if (ft_strchr(args[i + 1], '=') == NULL)
		{
			if (!check_identifier(args[i + 1]))
				printf("minishell: export: '%s': not a valid identifier\n", args[i + 1]);
			else
				check_if_exist(data, data->env, args, i);
			i++;
			continue ;
		}
		id = get_identifier(data, args[i + 1]);
		value = get_value(data, args[i + 1]);
		if (!check_identifier(id))
			printf("minishell: export: '%s': not a valid identifier\n", id);
		else if (check_identifier(id) == 2)
			plus_equal_condition(data, args[i + 1], 1);
		else if (!already_in_struct(data->env, id, value, 0))
		{
			add_in_env(data, args, i, 1);
		}
		free_id_value(id, value);
		i++;
	}
	return (0);
}
