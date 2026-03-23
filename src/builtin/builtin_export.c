/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:11:40 by haoky             #+#    #+#             */
/*   Updated: 2026/03/20 17:30:52 by haoky            ###   ########.fr       */
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

static void	wrapper_check_if_no_egal(char **args, t_data *data, int i)
{
	if (!check_identifier(args[i + 1]))
		printf("minishell: export: '%s': not a valid identifier\n",
			args[i + 1]);
	else
		check_if_exist(data, data->env, args, i);
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
			wrapper_check_if_no_egal(args, data, i);
			i++;
			continue ;
		}
		id = get_identifier(data, args[i + 1]);
		value = get_value(data, args[i + 1]);
		if (!check_identifier(id))
			printf("minishell: export: '%s': not a valid identifier\n", id);
		else if (check_identifier(args[i + 1]) == 2)
		{
			printf("cest bon\n");
			plus_equal_condition(data, args[i + 1], id, 1);
		}
		else if (!already_in_struct(data, id, value))
			add_in_env(data, args, i, 1);
		free_id_value(id, value);
		i++;
	}
	return (0);
}
