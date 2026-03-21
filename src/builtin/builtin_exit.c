/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:08:35 by jroh              #+#    #+#             */
/*   Updated: 2026/03/21 20:50:18 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	exit_with_code(t_data *data, long long code)
{
	free_data_except_env(data);
	free_env(data->env);
	exit(code);
}

int	exec_exit(t_data *data, char **args)
{
	long long	code;

	if (data->cmd_table->next == NULL)
		printf("exit\n");
	if (!args[1])
	{
		code = data->last_status;
		exit_with_code(data, code);
	}
	if (!is_valid_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit_with_code(data, 2);
	}
	if (count_args(args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atoll(args[1]);
	free_data_except_env(data);
	free_env(data->env);
	if (code > 255)
		exit(code % 256);
	exit(code);
}
