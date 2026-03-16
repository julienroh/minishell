/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:11:40 by haoky             #+#    #+#             */
/*   Updated: 2026/03/14 15:37:09 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_id_value(char *id, char *value)
{
	free(id);
	free(value);
}

static void	check_if_exist(t_env *env, char *arg)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, arg, ft_strlen(arg))
			&& (ft_strlen(tmp->id) == ft_strlen(arg)))
			tmp->printable = 1;
		tmp = tmp->next;
	}
}

static void	add_in_env(t_data *data, char **args, int i)
{
	t_env	*new;

	new = env_new(data, args[i + 1]);
	new->printable = 1;
	env_add_back(&data->env, new);
}

/*Check if the id already exist, if that's the case, we only replace the old
value by the new one. If not, we create a new space for the new id and value.
*/

void	exec_export(t_data *data, char **args, int i)
{
	char	*id;
	char	*value;

	if (!args[1])
		return (only_export(data, i));
	while (args[i + 1])
	{
		if (ft_strchr(args[i + 1], '=') == NULL)
		{
			check_if_exist(data->env, args[i + 1]);
			i++;
			continue ;
		}
		id = get_identifier(data, args[i + 1]);
		value = get_value(data, args[i + 1]);
		if (!check_identifier(id))
			invalid_export(id, value, args[i + 1]);
		else if (check_identifier(id) == 2)
			plus_equal_condition(data, args[i + 1], 1);
		else if (!already_in_struct(data->env, id, value, 0))
			add_in_env(data, args, i);
		free_id_value(id, value);
		i++;
	}
}
