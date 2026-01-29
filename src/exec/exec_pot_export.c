/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pot_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:21:05 by haoky             #+#    #+#             */
/*   Updated: 2026/01/24 18:10:42 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_pot_export(char *arg, t_env *env)
{
	char	*id;
	char	*value;
	t_env	*new;

	id = get_identifier(arg);
	value = get_value(arg);
	if (!check_identifier(id))
		invalid_export(id, value, arg);
	else if (check_identifier(id) == 2)
		plus_equal_condition(env, arg, 0);
	else if (!already_in_struct(env, id, value, 0))
	{
		new = env_new(arg);
		new->printable = 0;
		env_add_back(&env, new);
	}
}

int	exec_pot_export(char **args, t_env *env)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') == NULL)
			printf("minishell: %s: command not found\n", args[i + 1]);
		else
			put_pot_export(args[i], env);
		i++;
	}
	return (0);
}
