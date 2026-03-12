/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pot_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:21:05 by haoky             #+#    #+#             */
/*   Updated: 2026/03/12 10:45:19 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_pot_export(t_data *data, int i)
{
	char	*id;
	char	*value;
	t_env	*new;

	id = get_identifier(data, data->args[i]);
	value = get_value(data, data->args[i]);
	if (!check_identifier(id))
		invalid_export(id, value, data->args[i]);
	else if (check_identifier(id) == 2)
		plus_equal_condition(data, data->args[i], 0);
	else if (!already_in_struct(data->env, id, value, 0))
	{
		new = env_new(data, data->args[i]);
		new->printable = 0;
		env_add_back(&data->env, new);
	}
	free(id);
	free(value);
}

int	exec_pot_export(t_data *data)
{
	int		i;

	i = 0;
	while (data->args[i])
	{
		if (ft_strchr(data->args[i], '=') == NULL)
		{
			printf("pot_export\n");
			printf("minishell: %s: command not found\n", data->args[i + 1]);
			free_all(data);
		}
		else
			put_pot_export(data, i);
		i++;
	}
	return (0);
}
