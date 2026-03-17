/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:08:35 by jroh              #+#    #+#             */
/*   Updated: 2026/03/17 14:13:07 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	exec_exit(t_data *data, char **args)
{
	if (count_args(args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	free_data_except_env(data);
	free_env(data->env);
	if (args[1])
	{
		return (data->last_status);
	}
	return (0);
}
